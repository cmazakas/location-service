# Location Service

This is a micro-service intended to be used in service-oriented back-ends. The main purpose
is to help users find all other zip codes within a given radius of a supplied zip code.

So for example, if we wanted all cities within a 3 km radius of the 95833 zip code, we'd hit the service with:
```
GET localhost:3000/?zip=95833&radius=3000
```

and then we'd receive a JSON response from the service like:
```
[
    {
        "city": "Sacramento",
        "latitude": 38.642805,
        "longitude": -121.50466,
        "state": "CA",
        "zip": "95834"
    },
    {
        "city": "Sacramento",
        "latitude": 38.616891,
        "longitude": -121.49623,
        "state": "CA",
        "zip": "95833"
    }
]
```

The project is fueled by Microsoft's open-source project, the [cpprestsdk](https://github.com/Microsoft/cpprestsdk).

## Building

You will need CMake 3.6 and above to build this project.

### Windows

The easiest way to build this project on Windows is to download [vcpkg](https://github.com/Microsoft/vcpkg).

```
vcpkg install cpprestsdk:x64-windows boost:x64-windows catch:x64-windows
```

This will generate a CMake toolchain file that's located in `\vcpkg\scripts\buildsystem\vcpkg.cmake`.

You can then use CMake to generate the solution and then use MSBuild to build it. See `build.bat` for a working
example.

You can also simply build this using VS2017 by opening the containing folder once you've downloaded the repo.

### Linux

`cpprestsdk` is also available on Ubuntu as well among othe select distros like Arch.

For Ubuntu, simply use:
```
sudo apt-get install libcpprest-dev
```

You will also need Boost and [Catch](https://github.com/philsquared/Catch) so you'll need to see how your
specific distro wants you to build Boost. Catch is header-only so it simply just needs to exist on your computer
and in a location where CMake can find it.

## Using the service

Once you've build the service, it's simple to use it!

Simply query the service with `/?zip=...&radius=...` and it'll retrieve all cities within the supplied radius (radius is in meters).\

Type `exit` into the console to gracefully close the server.