_base_path='data/week3/part3TestCases/'

tests = []
test_results = []
tests += [_base_path+'unitTests/10/test{}.dict'.format(i) for i in xrange(0, 100)]
test_results += [_base_path+'unitTests/10/test{}.output'.format(i) for i in xrange(0, 100)]
tests += [_base_path+'unitTests/20/test{}.dict'.format(i) for i in xrange(0, 100)]
test_results += [_base_path+'unitTests/20/test{}.output'.format(i) for i in xrange(0, 100)]

# EPS = 0.001 is too small for the following tests:
#tests += [_base_path+'unitTests/50/test{}.dict'.format(i) for i in xrange(0, 100)]
#test_results += [_base_path+'unitTests/50/test{}.output'.format(i) for i in xrange(0, 100)]

task_result_path = 'results/homework31'
tasks = [_base_path+'assignmentParts/part{}.dict'.format(i) for i in xrange(1, 11)]
task_results = [task_result_path+'/part{}.output'.format(i) for i in xrange(1, 11)]


binary_path = 'build/homework31'
