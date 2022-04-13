#include <linux/module.h>

int width = 0;
module_param(width, int, S_IRUGO | S_IWUSR);

int heigh = 0;
module_param(heigh, int, S_IRUGO | S_IWUSR);

int matrix[1000];
module_param_array(matrix, int, NULL, S_IRUGO | S_IWUSR);


void SumOfMatrix(void) {
    int i, j, s = 0;
    for (i = 0; i < heigh; i++) {
        for (j = 0; j < width; j++) {
            s += matrix[i * width + j];
        }
    }
    printk("sum: %d\n", s);
}

void NegativePositive(void) {
    int N = 0, P = 0, i, j;
    for (i = 0; i < heigh; i++) {
        for (j = 0; j < width; j++) {
            if (matrix[i * width + j] > 0) {
                P++;
            }
            if (matrix[i * width + j] < 0) {
                N++;
            }
        }
    }    
    printk("Pos: %d\n", P);
    printk("Neg: %d\n", N);
}

void PrimarySecondary(void) {
    int min = matrix[0], max = matrix[0], i, diagonal;
    diagonal = (width < heigh)? width: heigh;
    for (i = 0; i < diagonal; i++) {
        if (min > matrix[i * width + i]) {
            min = matrix[i * width + i];
        }
        if (max < matrix[i * width + i]) {
            max = matrix[i * width + i];
        }
    }
    printk("min primary: %d\n", min);
    printk("max primary: %d\n", max);

    min = matrix[width - 1];
    max = matrix[width - 1];
    for (i = 0; i < diagonal; i++) {
        if (min > matrix[i * width + width - i - 1]) {
            min = matrix[i * width + width - i - 1];
        }
        if (max < matrix[i * width + width - i - 1]) {
            max = matrix[i * width + width - i - 1];
        }
    }
    printk("min secondary: %d\n", min);
    printk("max secondary: %d\n", max);
}

void OodEven(void) {
    int ood = 0, even = 0, i, j;
    for (i = 0; i < heigh; i++) {
        for (j = 0; j < width; j++) {
            if (matrix[i * width + j] % 2 == 0) {
                ood += matrix[i * width + j];
            } else {
                even += matrix[i * width + j];
            }
        }
    } 
    printk("ood: %d\n", ood);
    printk("even: %d\n", even);
}

static int md_init(void) {
    printk("init module\n");
    SumOfMatrix();
    NegativePositive();
    PrimarySecondary();
    OodEven();
    return 0;
}

static void md_exit(void) {
    printk("exit module\n");
}


module_init(md_init);
module_exit(md_exit);


MODULE_LICENSE("GPL");
