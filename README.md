# Audit

## How to build
```bash
mkdir ./build
cd ./build
cmake ..
make
```

## How to run
You should run __Audit__ in sudo mode
```bash
sudo ./Audit <pid>
```
or
```bash
sudo ./Audit `pidof <process name>`
```

## How to filter logs
```bash
cat ./audit.log | grep "\[39033\]"
```