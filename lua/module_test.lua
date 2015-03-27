--测试lua模块定义，以下是一种新的模块定义方式
--定义模块文件名时保持和模块名一致，require 根据文件名

local module_test = {}

function module_test.foo()
	print ("hello shok")
end

return module_test


-- for lua 5.0 or 5.1 or older
--[[
module("module_test", package.seeall)

function module_test.foo()
	print ("hello shok2")
end
--]]