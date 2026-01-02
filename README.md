# CRM

**Version** 0.0.1

**Language** C++20

**Status** - In development

## Requirements
- Cmake ? 3.20
- C++20 (MSVC 2022)

# Build
## Release
```bash
git clone https://github.com/Ichimonj/CRM.git
cd CrmSrc
mkdir build && cd build 
cmake ..
cmake --build . --config Release
```

## Debug and tests
```bash 
git clone https://github.com/Ichimonj/CRM.git
cd CrmSrc
mkdir build && cd build 
cmake .. -DBUILD_TESTING=ON
cmake --build . --config Debug
``` 
### Result
`Crm.exe` - main application.
`Tests.exe` - tests