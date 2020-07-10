Import("env")

build_flags = env.ParseFlags(env['BUILD_FLAGS'])
#print build_flags.get("CPPDEFINES")
flags = {k: v for (k, v) in build_flags.get("CPPDEFINES")}
#print flags
filename = "BIQU_S42B_V1." + flags.get("HARDWARE_VERSION") + "." + flags.get("SOFTWARE_VERSION")
#print filename
env.Replace(PROGNAME=filename)
