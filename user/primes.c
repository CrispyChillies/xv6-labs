#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void print_primes(int p[], int prime)
{
    if (prime == -1)
    {
        return;
    }

    uint32 num;
    read(p[0], &num, sizeof(uint32)); // Đọc số đầu tiên từ pipe vào num. 
    // Do ta bắt đầu với 2 
    // nên các giá trị sau của num sau dòng trên đều là số nguyên tố.
    printf("prime %d\n", num);

    int q[2]; // Mảng lưu 2 đầu của pipe khác.
    // Ta sẽ đẩy các giá trị không chia hết cho prime (số nguyên tố đang xét hiện tại) vào đây.
    pipe(q);
    int count = 1; // Biến đếm dùng để lưu lại số nguyên tố tiếp theo
    int next_prime = -1; // Số nguyên tố tiếp theo
    while (read(p[0], &num, sizeof(uint32)))
    {
        if (num % prime != 0) // Nếu giá trị đó không chia hết cho prime,
        {
            write(q[1], &num, sizeof(uint32)); // Đẩy giá trị đó vào pipe.
            
            if (count == 1) // Nếu đó là giá trị đầu tiên không chia hết cho prime,
            {
                next_prime = num; // thì nó là số nguyên tố tiếp theo.
                ++count;
            }
        }
    }
    close(q[1]); // Đóng đầu hút của pipe lại.

    print_primes(q, next_prime); // Gọi đệ quy trên pipe q và số nguyên tố tiếp theo.
}

void primes()
{
    int p[2]; // Mảng lưu 2 đầu của pipe.
    pipe(p); // Khởi tạo pipe.
    // Đẩy hết các số từ 2 đến 35 vào pipe.
    for (uint32 i = 2; i <= 35; ++i)
    {
        write(p[1], &i, sizeof(i));
    }
    close(p[1]); // Đóng đầu hút (write side) của pipe lại.

    print_primes(p, 2); // In các số nguyên tố, bắt đầu từ 2.
}

int
main(int argc, char *argv[])
{
    primes();
}