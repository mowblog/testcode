#include <stdio.h>
#include <string.h>

struct b_type {
    unsigned char depart: 3 ;   //部门(最大7个部门)
    unsigned char sex: 1 ;      //性别
    unsigned char reason: 2 ;   //理由(共4个)
};

void print(struct b_type *rea) {
    char dep[10];
    char sex[4];
    char res[10];

    switch (rea->depart) {
        case 1:
            strcpy(dep,"财务科");
            break;
        case 2:
            strcpy(dep,"开发科");
            break;
        case 3:
            strcpy(dep,"检测科");
            break;
        case 4:
            strcpy(dep,"生产科");
            break;
        default:
            break;
    }

    switch (rea->sex) {
        case 0:
            strcpy(sex,"男");
            break;
        default:
            strcpy(sex,"女");
            break;
    }

    switch (rea->reason) {
        case 1:
            strcpy(res,"事假");
            break;
        case 2:
            strcpy(res,"病假");
            break;
        case 3:
            strcpy(res,"婚假");
            break;
        default:
            strcpy(res,"无故");
            break;
    }

    printf("%s, %s, %s\n", dep, sex, res);

    return ;
}

int main(void)
{
    struct b_type staff; 

    staff.depart = 2;
    staff.sex = 0;
    staff.reason =3;

    printf("staff的长度：%d\n", sizeof(struct b_type));
    print(&staff);

    return 0;
}
