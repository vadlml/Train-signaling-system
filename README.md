# Simulation of a Train Signaling System:

### Build
```bash
git clone https://github.com/vadlml/Train-signaling-system.git
cd Train-signaling-system
mkdir build && cd build
cmake ../
make 
```
### Requirements:
```
nlohmann_json version "3.9.1"
```

### Usage: 
```
./TrainSig [FILE]... [OPTION]... 
Options: 
         -v - verbose output with event log messages;
Example: ./TrainSig input.json
```
### Prerequisites:
```
- Each track segment consist of of two track points linked one to each other
- All track segments are equal length
- Each track line consists of one or more track segments 
- Signals are optionally placed at the ends of each track segment
    • Green – train traffic is allowed through
    • Red – train traffic must stop before proceeding to the next track segment
- All trains are one track long 
- All trains are moving with same speed
- All junctions can direct train traffic only to one of the forked tracks at any given time.
```

### Input JSON file example:
```
input.json
{
	"lines": [
		[0,1,2,3,4,5,6],
		[3,7,8,9]
	],
	"trains": [
		{
			"id": 0,
			"dir": "Forward",
			"start_point id": 1
		},
		{
			"id": 1,
			"dir": "Reverse",
			"start_point id": 9
		}
	],
	"signals": [
		{
			"id": 0,
			"point id": 4
		},
		{
			"id": 1,
			"point id": 7
		}
	]
}
```
#### Corresponds to the following track lines:

```
    (T0)          (S0)
(0)--(1)--(2)--(3)--(4)--(5)--(6)
                |             
               (7)--(8--(9) 
                (S1)    (T1)
```
#### Where: 
##### (T0), (T1) - Train0 and Train1
##### (S0), (S1) - Signal1 and Signal2
