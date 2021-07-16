# Android-TV-Remote-Controller-Qt
Qt based gui application that control some of Android TVs and Android boxes, over network, using of ssl socket. Tested on `Mi Box4`

- Using upnp to discover devices
- Paring with devices and send key commands with ssl socket

Special thanks to [@Aymkdn](https://github.com/Aymkdn) for his detailed wiki. For more details about protocol check [here](https://github.com/Aymkdn/assistant-freebox-cloud/wiki/Google-TV-(aka-Android-TV)-Remote-Control).


## Tested on:
```
Mi Box4
```

## Requirements: 
* C++11
* Qt 5.12 and later
* Qt quick
* Qt virtualkeyboard
* Qt network
* Qt opcua

## prepair and run:
After Installing requirements, compile and run the application.
For the first time it will start discovery and pairing automatically.

After first time pairing, it works pithout pairing.
