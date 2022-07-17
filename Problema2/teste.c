int status;

// woman_wants_to_enter 
void woman_wants_to_enter()
{
  while (1)
  {
    pthread_mutex_lock();
    if (status != HAS_MAN)
    {
      status = HAS_WOMAN;
      women = women + 1;
      printf("Mulher entrou no Banheiro\n");
      pthread_mutex_unlock();
      break;
    }
    pthread_mutex_unlock();
  }
}

// man_wants_to_enter
void man_wants_to_enter()
{
  while (1)
  {

    pthread_mutex_lock();
    if (status != HAS_WOMAN)
    {
      status = HAS_MAN;
      men = men + 1;
      printf("Homem entrou no banheiro \n");
      pthread_mutex_unlock();
      break;
    }
    pthread_mutex_unlock();
  }
}

// woman_leaves 
void woman_leaves()
{
  pthread_mutex_lock();
  if (mulher == 1)
  {
    status = EMPTY
  };
  mulher = mulher - 1;
  printf("Mulher saiu o banheiro \n");
  pthread_mutex_unlock();
}

// man_leaves 
void man_leaves()
{
  pthread_mutex_lock();
  if (homem == 1)
  {
    status = EMPTY
  };
  homem = homem - 1;
  printf("Homem saiu do banheiro\n");
  pthread_mutex_unlock();
}