extern int main(); //int argc, char **argv, char **environ);
extern int CPU_BSS_START, CPU_BSS_END; // BSS should be the last think before _end

// TODO: environment
//char *__env[1] = { 0 };
//char **environ = __env;

int kvm_kickstart()
{
  int *i;

  // zero BSS
  for(i = (int *) CPU_BSS_START; i < (int *) CPU_BSS_END; i++)
  {
    *i = 0;
  }

  // TODO: get argc and argv
//  exit(main(0,0, __env));
  main();
}
