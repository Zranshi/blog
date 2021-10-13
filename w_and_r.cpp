semaphore r, w;  // r为读者信号量, w为写者信号量
int read_count;  // 记录有多少个读者正在读

void reader() {
  while (1) {
    wait(r);
    if (read_count == 0) {
      wait(w);
    }
    read_count++;
    signal(r);

    // read something

    wait(r);
    read_count--;
    if (read_count == 0) {
      signal(w);
    }
    signal(r);
  }
  return;
}

void writer() {
  while (1) {
    wait(w);

    // update/read something...

    signal(w);
  }
  return;
}
