/*
	large prime sample for 64-bit arch
	make CFLAGS_USER="-DMCL_MAX_OP_BIT_SIZE=768"
*/
#include <mcl/fp.hpp>
#include <cybozu/benchmark.hpp>

typedef mcl::FpT<> Fp;

void test(mcl::fp::Mode mode)
{
	printf("test %s\n", mcl::fp::ModeToStr(mode));
	std::string pStr = "776259046150354467574489744231251277628443008558348305569526019013025476343188443165439204414323238975243865348565536603085790022057407195722143637520590569602227488010424952775132642815799222412631499596858234375446423426908029627";
	Fp::init(pStr, mode);
	mpz_class p(pStr);
	Fp x = 123456;
	Fp::pow(x, x, p);
	std::cout << x << std::endl;
	CYBOZU_BENCH("mul", Fp::mul, x, x, x);
}
int main()
	try
{
	test(mcl::fp::FP_GMP);
	test(mcl::fp::FP_GMP_MONT);
#ifdef MCL_USE_LLVM
	test(mcl::fp::FP_LLVM);
	test(mcl::fp::FP_LLVM_MONT);
#endif
} catch (std::exception& e) {
	printf("err %s\n", e.what());
	puts("make clean");
	puts("make CFLAGS_USER=\"-DMCL_MAX_OP_BIT_SIZE=768\"");
	return 1;
}
