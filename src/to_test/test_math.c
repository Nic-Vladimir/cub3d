#include "math.c"
#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>

void	test_add(void)
{
	CU_ASSERT(add(2, 9) == 11);
	CU_ASSERT(add(-6, 24) == 18);
	CU_ASSERT(add(0, 0) == 0);
}

void	test_sub(void)
{
	CU_ASSERT(sub(325, 300) == 25);
	CU_ASSERT(sub(17, 20) == -3);
	CU_ASSERT(sub(0, 0) == 0);
}

int	main(void)
{
	CU_pSuite	suite;

	if (CUE_SUCCESS != CU_initialize_registry())
		return (CU_get_error());
	suite = CU_add_suite("Math Suite", NULL, NULL);
	if (!suite)
	{
		CU_cleanup_registry();
		return (CU_get_error());
	}
	if ((NULL == CU_add_test(suite, "test add()", test_add))
		|| (NULL == CU_add_test(suite, "test sub()", test_sub)))
	{
		CU_cleanup_registry();
		return (CU_get_error());
	}
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return (CU_get_error());
}
