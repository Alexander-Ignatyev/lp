_base_path='data/week2/part2TestCases/'

tests = []
test_results = []
tests += [_base_path+'unitTests/dict{}'.format(i) for i in xrange(1, 11)]
test_results += [_base_path+'unitTests/dict{}.output'.format(i) for i in xrange(1, 11)]
tests += [_base_path+'moreUnitTests/test{}.dict'.format(i) for i in xrange(1, 110)]
test_results += [_base_path+'moreUnitTests/test{}.dict.output'.format(i) for i in xrange(1, 110)]

task_result_path = 'results/homework22'
tasks = [_base_path+'assignmentParts/part{}.dict'.format(i) for i in xrange(1, 6)]
task_results = [task_result_path+'/part{}.dict.output'.format(i) for i in xrange(1, 6)]

binary_path = 'build/homework22'
