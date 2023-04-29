include(FetchContent)
FetchContent_Declare(cpr
	GIT_REPOSITORY https://github.com/libcpr/cpr.git
	GIT_TAG 32fd1453194c37d5136577ee55629b863a42333f)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(jsoncpp 
	GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
	GIT_TAG 5defb4ed1a4293b8e2bf641e16b156fb9de498cc)
FetchContent_MakeAvailable(jsoncpp)

add_library(VimeCpp STATIC  
	"client.cpp"
	"guild.cpp"
	"leaderboard.cpp"
	"locale.cpp"
	"match.cpp"
	"misc.cpp"
	"online.cpp"
	"user.cpp"
	"utils.cpp"
)
target_compile_features(VimeCpp PUBLIC cxx_std_17)
target_include_directories(VimeCpp PUBLIC "../include")
target_link_libraries(VimeCpp PUBLIC cpr)
target_link_libraries(VimeCpp PUBLIC jsoncpp_lib)