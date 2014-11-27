_base_path='data/week6/ilpTests/'

tests = []
test_results = []
tests += [_base_path+'unitTests/ilpTest{}'.format(i) for i in xrange(0, 11)]
test_results += [_base_path+'unitTests/ilpTest{}.output'.format(i) for i in xrange(0, 11)]

# not all tests are passed.
# e.g. for tests 2 on one of steps we obtain an answer with right objective value
# but some of basic variables are non-integers,
# at the same time in tex-file all these values are integers
# tests += [_base_path+'unitTests/test{}'.format(i) for i in xrange(0, 100)]
# test_results += [_base_path+'unitTests/test{}.output'.format(i) for i in xrange(0, 100)]

task_result_path = 'results/homework61'
tasks = [_base_path+'assignmentTests/part{}.dict'.format(i) for i in xrange(1, 6)]
task_results = [task_result_path+'/part{}.dict.output'.format(i) for i in xrange(1, 6)]

binary_path = 'build/homework61'
