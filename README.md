# Audit

## BUILD
```bash
mkdir ./build
cd ./build
cmake ..
make
```

## IN _/build_ DIRECTORY:

### RUN
(only in __sudo__ mode)
```bash
sudo ./Audit <pid>
```
or
```bash
sudo ./Audit `pidof <process name>`
```

### LOG FILTER
```bash
cat ./audit.log | grep "\[<pid>\]"
```
