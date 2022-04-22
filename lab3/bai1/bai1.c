#include <linux/module.h>


// khoi tao vector1
int vector1[100];
int len_vector1;
module_param_array(vector1, int, &len_vector1, S_IRUGO);

// khoi tao vector2
int vector2[100];
int len_vector2;
module_param_array(vector2, int, &len_vector2, S_IRUGO);

// khoi tao ma tran 1
int width_1;
int height_1;
int num_1;
int matrix1[100];
module_param(width_1, int, S_IRUGO);
module_param(height_1, int , S_IRUGO);
module_param_array(matrix1, int , &num_1, S_IRUGO);

// khoi tao ma tran 2
int width_2;
int height_2;
int num_2;
int matrix2[100];
module_param(width_2, int, S_IRUGO);
module_param(height_2, int, S_IRUGO);
module_param_array(matrix2, int, &num_2, S_IRUGO);

// tich chap nAk
int n;
int k;
module_param(n, int, S_IRUGO);
module_param(k, int, S_IRUGO);

static int md_init(void) {
    int i, j, h, tichvh = 0, chinh_hop = 1;

    int matrix3[100];

    printk("start module\n");
    
    // tich vo huong 2 vector
    if (len_vector1 == len_vector2) {
        for (i = 0; i < len_vector1; i++) {
            tichvh = vector1[i] * vector2[i];
        }

        printk("tich vo huong 2 vector: %d\n", tichvh);
    }
    // -----

    // tong 2 ma tran
    printk("tong 2 ma tran: \n");
    if (num_1 == width_1 * height_1 && num_2 == width_2 * height_2 && width_1 == width_2 && height_1 == height_2) {  // check ma tran
        for (i = 0; i < height_1; i++) {
            for (j = 0; j < width_1; j++) {
                matrix3[i * width_1 + j] = matrix1[i * width_1 + j] + matrix2[i * width_1 + j];
            }
        }

        for (i = 0; i < height_1; i++) {
            for (j = 0; j < width_1; j++) {
                printk("matrix[%d][%d]: %d\n", i, j, matrix3[i * width_1 + j]);
            }
        }
    }

    // ------

    // hieu 2 ma tran
    printk("hieu 2 ma tran: \n");
    if (num_1 == width_1 * height_1 && num_2 == width_2 * height_2 && width_1 == width_2 && height_1 == height_2) {  // check ma tran
        for (i = 0; i < height_1; i++) {
            for (j = 0; j < width_1; j++) {
                matrix3[i * width_1 + j] = matrix1[i * width_1 + j] - matrix2[i * width_1 + j];
            }
        }

        for (i = 0; i < height_1; i++) {
            for (j = 0; j < width_1; j++) {
                printk("matrix[%d][%d]: %d\n", i, j, matrix3[i * width_1 + j]);
            }
        }
    }

    // ------

    // nhan 2 ma tran
    printk("nhan 2 ma tran\n");
    if (width_2 == height_1) {
        for (i = 0; i < height_2; i++) {
            for (j = 0; j < width_1; j++) {
                matrix3[i * width_1 + j] = 0;
                for (h = 0; h < width_2; h++) {
                    matrix3[i * width_1 + j] += matrix1[i * width_1 + h] * matrix2[h * width_1 + j];
                }
            }
        }

        for (i = 0; i < height_1; i++) {
            for (j = 0; j < width_1; j++) {
                printk("matrix[%d][%d]: %d\n", i, j, matrix3[i * width_1 + j]);
            }
        }
    }

    // -------

    // chinh hop nAk
    for (i = n; i >= n - k + 1; i--) {
        chinh_hop = chinh_hop * i;
        printk("cd: %d\n", chinh_hop);
    }
    printk("chinh hop %d cua %d la: %d\n", k, n, chinh_hop);

    return 0;
}

static void md_exit(void) {
    printk("exit module\n");
}


module_init(md_init);
module_exit(md_exit);


MODULE_LICENSE("GPL");