import 'package:flutter/material.dart';

void main() {
  runApp(CatMonitorApp());
}

class CatMonitorApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Cat Activity Monitor',
      theme: ThemeData(
        primarySwatch: Colors.orange,
      ),
      home: CatHomePage(),
    );
  }
}

class CatHomePage extends StatefulWidget {
  @override
  _CatHomePageState createState() => _CatHomePageState();
}

class _CatHomePageState extends State<CatHomePage> {
  int _steps = 0;
  int _meals = 0;
  int _sleepHours = 0;

  void _incrementSteps() {
    setState(() {
      _steps += 100; // Symulacja kroków
    });
  }

  void _incrementMeals() {
    setState(() {
      _meals++;
    });
  }

  void _incrementSleep() {
    setState(() {
      _sleepHours += 1;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Cat Activity Monitor'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: [
            // Obraz kota
            Image.asset('assets/images/cat.png', height: 200),
            SizedBox(height: 20),
            // Licznik kroków
            Card(
              child: ListTile(
                title: Text('Steps'),
                trailing: Text('$_steps steps'),
                leading: Icon(Icons.directions_walk),
              ),
            ),
            SizedBox(height: 10),
            // Licznik posiłków
            Card(
              child: ListTile(
                title: Text('Meals'),
                trailing: Text('$_meals meals'),
                leading: Icon(Icons.fastfood),
              ),
            ),
            SizedBox(height: 10),
            // Licznik godzin snu
            Card(
              child: ListTile(
                title: Text('Sleep Hours'),
                trailing: Text('$_sleepHours hours'),
                leading: Icon(Icons.bedtime),
              ),
            ),
            SizedBox(height: 20),
            // Przyciski do aktualizacji danych
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: [
                ElevatedButton(
                  onPressed: _incrementSteps,
                  child: Text('Add Steps'),
                ),
                ElevatedButton(
                  onPressed: _incrementMeals,
                  child: Text('Add Meal'),
                ),
                ElevatedButton(
                  onPressed: _incrementSleep,
                  child: Text('Add Sleep'),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
