
dofile("precore_import.lua")
local S, G, P = precore.helpers()

precore.make_config("am.test-strict", nil, {
{project = function()
	configuration {}
		flags {
			"FatalWarnings"
		}

	configuration {"linux"}
		buildoptions {
			"-pedantic-errors",
			"-Wextra",

			"-Wuninitialized",
			"-Winit-self",

			"-Wmissing-field-initializers",
			"-Wredundant-decls",

			"-Wold-style-cast",

			"-Wnon-virtual-dtor",
			"-Woverloaded-virtual",

			"-Wunused",
			"-Wundef",
		}
end}})

function make_test(group, name, srcglob, configs)
	precore.make_project(
		group .. "_" .. name,
		"C++", "ConsoleApp",
		"./", "out/",
		nil, configs
	)

	if configs == nil then
		precore.apply("am.test-strict")
	end

	if srcglob == nil then
		srcglob = name .. ".cpp"
	end

	configuration {}
		targetname(name)
		includedirs {
			S"${ROOT}/",
		}
		files {
			srcglob
		}

	configuration {"linux"}
		targetsuffix(".elf")
end

function make_tests(group, tests)
	for name, test in pairs(tests) do
		make_test(group, name, test[0], test[1])
	end
end

precore.init(
	{
		-- Don't have a top-level premake script, so forcing project
		-- root to top-level
		ROOT = path.getabsolute("..")
    },
	{
		"precore.clang-opts",
		"precore.c++11-core",
		"precore.env-common",
	}
)

-- Test solution

precore.make_solution(
	"test",
	{"debug", "release"},
	{"x64", "x32"},
	nil, {
		"precore.generic",
	}
)

-- Groups

precore.import("general")
precore.import("vec")
precore.import("mat")
precore.import("hash")

precore.action_clean("out")
