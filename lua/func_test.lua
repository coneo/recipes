
func_test = {}

function foo()
	print "haha foo"
	eat()
end

eat = function ()
	print "haha eat"
end

function func_test.test()
	foo()
end

return func_test