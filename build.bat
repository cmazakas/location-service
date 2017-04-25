mkdir .\build
mkdir .\bin
cd .\build

set build_type=Debug

cmake ^
  -DCMAKE_INSTALL_PREFIX=.. ^
  -DCMAKE_BUILD_TYPE=%build_type% ^
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake ^
  -G "Visual Studio 15 2017 Win64" ^
  .. &&^
msbuild location_service.sln /m /p:Configuration=%build_type% && ^
msbuild INSTALL.vcxproj /m /p:Configuration=%build_type%

cd ..