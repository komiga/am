
local S, G, R = precore.helpers()

precore.make_config_scoped("am.env", {
	once = true,
}, {
{global = function()
	precore.define_group("AM", os.getcwd())
end}})

precore.make_config("am.strict", nil, {
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

precore.make_config("am.dep", nil, {
{project = function()
	configuration {}
		includedirs {
			G"${AM_ROOT}/",
		}
end}})

precore.apply_global({
	"precore.env-common",
	"am.env",
})
