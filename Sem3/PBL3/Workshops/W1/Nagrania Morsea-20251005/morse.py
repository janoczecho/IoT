# morse_decode_auto.py
import sys
import numpy as np
import librosa
from scipy.signal import butter, filtfilt, find_peaks, hilbert
from sklearn.cluster import KMeans

MORSE_CODE_DICT = {
    '.-':'A', '-...':'B', '-.-.':'C', '-..':'D', '.':'E', '..-.':'F',
    '--.':'G', '....':'H', '..':'I', '.---':'J', '-.-':'K', '.-..':'L',
    '--':'M', '-.':'N', '---':'O', '.--.':'P', '--.-':'Q', '.-.':'R',
    '...':'S', '-':'T', '..-':'U', '...-':'V', '.--':'W', '-..-':'X',
    '-.--':'Y', '--..':'Z',
    '-----':'0', '.----':'1', '..---':'2', '...--':'3', '....-':'4',
    '.....':'5', '-....':'6', '--...':'7', '---..':'8', '----.':'9'
}

def decode_morse(morse_sequence):
    words = morse_sequence.strip().split('   ')
    decoded_words = []
    for word in words:
        letters = word.split()
        decoded_letters = [MORSE_CODE_DICT.get(l, '?') for l in letters]
        decoded_words.append(''.join(decoded_letters))
    return ' '.join(decoded_words)

def bandpass_filter(y, low, high, sr, order=4):
    nyq = 0.5 * sr
    lown = max(low / nyq, 1e-6)
    highn = min(high / nyq, 0.999999)
    b, a = butter(order, [lown, highn], btype='band')
    return filtfilt(b, a, y)

def group_close(freqs, tol_hz=30):
    if len(freqs) == 0:
        return []
    freqs_sorted = np.sort(freqs)
    groups = []
    current = [freqs_sorted[0]]
    for f in freqs_sorted[1:]:
        if f - current[-1] <= tol_hz:
            current.append(f)
        else:
            groups.append(np.mean(current))
            current = [f]
    groups.append(np.mean(current))
    return np.array(groups)

def analyze_and_decode(path, freq_low=300, freq_high=3000, n_fft=2048, hop_length=512):
    print(f"Ładuję: {path}")
    y, sr = librosa.load(path, sr=None, mono=True)
    print(f"Próbkowanie: {sr} Hz, długość: {len(y)/sr:.2f} s")

    # STFT + średnia amplituda per częstotliwość
    D = np.abs(librosa.stft(y, n_fft=n_fft, hop_length=hop_length))
    amp_per_freq = D.mean(axis=1)
    freqs = librosa.fft_frequencies(sr=sr, n_fft=n_fft)

    # Maskujemy pasmo zainteresowania
    mask = (freqs >= freq_low) & (freqs <= freq_high)
    amp_mask = amp_per_freq[mask]
    freq_mask = freqs[mask]

    if len(amp_mask) == 0:
        print("Brak pasma w zadanym zakresie.")
        return

    # Szukamy szczytów w masce (z minimalną prominencją)
    peaks, props = find_peaks(amp_mask, height=np.max(amp_mask)*0.2, prominence=np.max(amp_mask)*0.05)
    peak_freqs = freq_mask[peaks] if len(peaks) else np.array([])

    if len(peak_freqs) == 0:
        # fallback: wybierz top N
        idx = np.argsort(amp_mask)[-3:]
        peak_freqs = freq_mask[idx]
    # grupujemy blisko leżące częstotliwości
    centers = group_close(peak_freqs, tol_hz=30)
    print("Znalezione skupienia tonów (Hz):", ", ".join(f"{c:.1f}" for c in centers))

    results = []
    for center in centers:
        low = center - 40
        high = center + 40
        print(f"\nAnaliza tonu ~{center:.1f} Hz (filtr {low:.1f}–{high:.1f} Hz)")
        try:
            y_filt = bandpass_filter(y, low, high, sr, order=4)
        except Exception as e:
            print("Błąd filtra:", e)
            continue

        # obwiednia sygnału (analytic signal)
        analytic = hilbert(y_filt)
        env = np.abs(analytic)
        # uśrednienie ruchome (oka 10-20 ms) aby wygładzić
        win_ms = 0.015
        win = max(1, int(win_ms * sr))
        kernel = np.ones(win) / win
        env_smooth = np.convolve(env, kernel, mode='same')
        # framing (non-overlap) dla prostoty: frame_size = 10 ms
        frame_s = 0.01
        frame_n = max(1, int(frame_s * sr))
        frames = np.array([np.sum(env_smooth[i:i+frame_n]) for i in range(0, len(env_smooth), frame_n)])
        t_frames = np.arange(len(frames)) * frame_s

        # adaptacyjny threshold: mediana + k * std
        med = np.median(frames)
        std = np.std(frames)
        thr = med + 0.5 * std
        # ale jeżeli med very small, użyj % max
        if med < 1e-9:
            thr = 0.2 * np.max(frames)

        binary = (frames > thr).astype(int)

        # usuń krótkie przebłyski (drobne błędy)
        # złącz/usuń impulsy krótsze niż min_len frames
        min_len_frames = max(1, int(0.02 / frame_s))  # 20 ms minimalny impuls
        # cleanup function
        def cleanup_binary(b, minlen):
            out = b.copy()
            i = 0
            while i < len(out):
                j = i
                while j < len(out) and out[j] == out[i]:
                    j += 1
                length = j - i
                if length < minlen:
                    out[i:j] = 0 if out[i] == 1 else 1
                i = j
            return out
        binary = cleanup_binary(binary, min_len_frames)

        # znajdowanie ciągłych odcinków
        on_lengths = []
        off_lengths = []
        i = 0
        L = len(binary)
        while i < L:
            val = binary[i]
            j = i
            while j < L and binary[j] == val:
                j += 1
            length_frames = j - i
            if val == 1:
                on_lengths.append(length_frames * frame_s)
            else:
                off_lengths.append(length_frames * frame_s)
            i = j

        if len(on_lengths) == 0:
            print("Brak wykrytych tonów po filtracji.")
            continue

        # Klasteryzacja długości tonów (log-scale) na 2 grupy (kropka/kreska)
        X = np.log(np.array(on_lengths).reshape(-1,1) + 1e-9)
        if len(X) >= 2:
            kmeans = KMeans(n_clusters=2, random_state=0).fit(X)
            centers_d = np.exp(kmeans.cluster_centers_.flatten())
            idx_dot = np.argmin(centers_d)
            dot_mean = centers_d[idx_dot]
            dash_mean = centers_d[1-idx_dot]
        else:
            # tylko jeden typ: traktujemy jako kropki
            dot_mean = np.median(on_lengths)
            dash_mean = dot_mean * 3.0

        unit = dot_mean
        bitrate = 1.0 / unit if unit > 0 else float('nan')
        print(f"Estymowany czas kropki: {unit:.3f} s  (bitrate ≈ {bitrate:.2f} bit/s)")
        print(f"Średni czas kreski (est): {dash_mean:.3f} s")

        # teraz zbuduj sekwencję morse'a
        morse_seq = ""
        i = 0
        while i < len(binary):
            if binary[i] == 1:
                # on
                j = i
                while j < len(binary) and binary[j] == 1:
                    j += 1
                dur = (j - i) * frame_s
                # klasyfikacja
                if dur < (unit * 1.8):
                    morse_seq += "."
                else:
                    morse_seq += "-"
                i = j
            else:
                # off
                j = i
                while j < len(binary) and binary[j] == 0:
                    j += 1
                dur = (j - i) * frame_s
                if dur < (unit * 1.5):
                    # przerwa między elementami tej samej litery -> nic
                    pass
                elif dur < (unit * 4.0):
                    # przerwa między literami
                    morse_seq += " "
                else:
                    # przerwa między słowami
                    morse_seq += "   "
                i = j

        decoded = decode_morse(morse_seq)
        print("\nSekwencja Morse'a (przybliżona):")
        print(morse_seq)
        print("\nZdekodowany tekst (próba):")
        print(decoded)

        results.append({
            "center_freq": center,
            "unit": unit,
            "bitrate": bitrate,
            "morse_seq": morse_seq,
            "decoded": decoded
        })

    if not results:
        print("Nie znaleziono nic do zdekodowania.")
    else:
        print("\n---- Podsumowanie ----")
        for r in results:
            print(f"Ton ~{r['center_freq']:.1f} Hz: dot={r['unit']:.3f}s, bitrate≈{r['bitrate']:.2f} bit/s, decoded='{r['decoded']}'")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Użycie: python morse_decode_auto.py <plik.mp3>")
    else:
        analyze_and_decode(sys.argv[1])
