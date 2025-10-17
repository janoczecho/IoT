# analyse_morse_mp3.py
import sys
import numpy as np
import librosa
import scipy.signal as signal
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

def envelope(y, sr, win_ms=10):
    # RMS envelope with moving window (win_ms milliseconds)
    win = int(sr * win_ms / 1000)
    if win < 1: win = 1
    y2 = y**2
    kernel = np.ones(win)/win
    rms = np.sqrt(np.convolve(y2, kernel, mode='same'))
    return rms

def detect_on_off(rms, sr, threshold=None):
    # auto threshold: percentile if not provided
    if threshold is None:
        threshold = np.percentile(rms, 75) * 0.5  # heurystyka
    on = rms > threshold
    # remove very short blips
    min_samples = int(0.005 * sr)  # 5 ms
    on = signal.medfilt(on.astype(float), kernel_size=3).astype(bool)
    # return transitions
    changes = np.diff(on.astype(int))
    starts = np.where(changes == 1)[0] + 1
    ends = np.where(changes == -1)[0] + 1
    if on[0]:
        starts = np.concatenate(([0], starts))
    if on[-1]:
        ends = np.concatenate((ends, [len(on)]))
    return starts, ends, on, threshold

def durations_from_starts_ends(starts, ends, sr):
    lengths_s = (ends - starts) / float(sr)
    return lengths_s

def cluster_durations(durations):
    # cluster into 2 groups (dots and dashes) using kmeans on log durations
    X = np.log(np.array(durations).reshape(-1,1) + 1e-9)
    kmeans = KMeans(n_clusters=2, random_state=0).fit(X)
    labels = kmeans.labels_
    centers = np.exp(kmeans.cluster_centers_.flatten())
    # identify which center is dot (shorter)
    idx_dot = np.argmin(centers)
    dot_durations = np.array(durations)[labels == idx_dot]
    dash_durations = np.array(durations)[labels != idx_dot]
    return dot_durations, dash_durations, centers

def main(path, plot=True):
    y, sr = librosa.load(path, sr=None, mono=True)  # keeps original sample rate; does NOT convert file
    rms = envelope(y, sr, win_ms=6)  # drobne okno
    starts, ends, on, threshold = detect_on_off(rms, sr, threshold=None)
    seg_durations = durations_from_starts_ends(starts, ends, sr)

    if len(seg_durations) == 0:
        print("Nie wykryto żadnych tonów. Spróbuj zmniejszyć próg lub sprawdzić plik.")
        return

    # filtrowanie bardzo krótkich i długich (szum)
    seg_durations = seg_durations[(seg_durations > 0.005) & (seg_durations < 5.0)]

    if len(seg_durations) < 2:
        print("Za mało segmentów do analizy.")
        return

    dot_durs, dash_durs, centers = cluster_durations(seg_durations)

    mean_dot = dot_durs.mean() if len(dot_durs) else np.nan
    mean_dash = dash_durs.mean() if len(dash_durs) else np.nan
    ratio = mean_dash / mean_dot if (not np.isnan(mean_dot) and not np.isnan(mean_dash)) else np.nan
    bitrate = 1.0 / mean_dot if not np.isnan(mean_dot) else np.nan

    print(f"Plik: {path}")
    print(f"Próg RMS użyty: {threshold:.5g}")
    print(f"Liczba segmentów: {len(seg_durations)}")
    print(f"Średni czas kropki: {mean_dot:.4f} s")
    print(f"Średni czas kreski: {mean_dash:.4f} s")
    print(f"Stosunek kreska/kropka ≈ {ratio:.2f} (oczekane ~3.0)")
    print(f"Prędkość transmisji (przy 1 kropce = 1 bit): {bitrate:.2f} bit/s")

    if plot:
        times = np.arange(len(y))/sr
        plt.figure(figsize=(12,5))
        plt.plot(times, y, alpha=0.5)
        plt.plot(times, rms / np.max(rms) * 0.5, label='RMS (znormalizowany)')
        for s,e in zip(starts, ends):
            plt.axvspan(s/sr, e/sr, color='orange', alpha=0.3)
        plt.title('Sygnał i wykryte tony (pola pomarańczowe)')
        plt.xlabel('Czas [s]')
        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Użycie: python analyse_morse_mp3.py ścieżka/do/pliku.mp3")
    else:
        main(sys.argv[1])
