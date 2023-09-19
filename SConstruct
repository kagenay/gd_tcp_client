env = SConscript('godot-cpp/SConstruct')

libpath = ""

env.Append(CPPPATH=["src/"])
sources = (Glob("src/*.cpp"))
sources += (Glob("libs/tcp_client/*.cpp"))
env.Append(LIBS=["ws2_32"])

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "../libtest.{}.{}.framework/libtest.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    if env["suffix"] == ".android.template_debug.arm64":
        libpath = "../bin/debug/android/arm64/"
    elif env["suffix"] == ".android.template_release.arm64":
        libpath = "../bin/release/android/arm64/"
    elif env["suffix"] == ".windows.template_debug.x86_64":
        libpath = "../bin/debug/windows/x86_64/"

    library = env.SharedLibrary(
        "{}libg{}".format(libpath, env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
