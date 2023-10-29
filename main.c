#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_TERMS 101
#define MAX_COL 10 // 이론상 COL 1~300, ROW 300~1 까지 가능하지만, 보여지는 데 무리가 있어서 제한함
#define MAX_ROW 10

typedef struct term {
    int row;
    int col;
    int value;
} term;

void selectMenu();

void makeRandomSparseMatrix(term a[]);
void makeSparseMatrix(term a[]);
void makeDefaultMatrix(term a[]);

void deleteDuplicateData(term a[]);
void sortingSparseMatrix(term a[]);

void transposeAndPrintTwoWay(term a[], term b[]);
void fastTranspose(term a[], term b[]);
void fastTranspose_lagacy(term a[], term b[]);
void printMatrix_RepresentationOfSparseMatrix(term a[]);
void printMatrix(term a[]);

int main() {
    selectMenu();

    return 0;
}

void selectMenu() {
    srand(time(NULL));
    while (1) {
        term a[MAX_TERMS];
        term a_transposed[MAX_TERMS];

        a[0].value = -1;

        printf("\n\n\n");
        printf("\t * 데이터 입력 모드를 선택하세요. (default - Random)\n");
        printf("\t| R : Random(랜덤) \t| U : User Input(수동 입력) \t| E : Example(예제) \t| Q : 나가기 \t \n");
        printf("\t: ");
        char mode = getchar();
        while (getchar() != '\n');
        printf("\n");

        if (mode == 'U') {
            printf("\t! 데이터를 수동으로 입력합니다.\n");

            printf("\t! 데이터 수동 입력 방식을 입력하세요 (defualt - Sparse Matrix Representation)\n");
            printf("\t| D : Default Matrix Representation(기본 표현법) \t| S : Sparse Matrix Representation(희소행렬 표현법) \t \n");
            printf("\t: ");
            char repre = getchar();
            while (getchar() != '\n');
            printf("\n");

            if(repre == 'D'){
                printf("\t| D : Default Matrix Representation(기본 표현법) \n");
                makeDefaultMatrix(a);
                transposeAndPrintTwoWay(a, a_transposed);
            }else  {
                printf("\t| S : Sparse Matrix Representation(희소행렬 표현법) \t \n");
                makeSparseMatrix(a);
                transposeAndPrintTwoWay(a, a_transposed);
            }
        }
        else if (mode == 'Q') {
            printf("\t! 종료합니다.\n");
            break;
        }
        else if (mode == 'E') {
            printf("\t! 데이터가 예제로 입력됩니다.\n");


            term b[MAX_TERMS];
            term b_transposed[MAX_TERMS];
            term c[MAX_TERMS];
            term c_transposed[MAX_TERMS];
            term d[MAX_TERMS];
            term d_transposed[MAX_TERMS];
            term e[MAX_TERMS];
            term e_transposed[MAX_TERMS];
            term f[MAX_TERMS];
            term f_transposed[MAX_TERMS];
            term g[MAX_TERMS];
            term g_transposed[MAX_TERMS];

            b[0].value = -1;
            c[0].value = -1;
            d[0].value = -1;
            e[0].value = -1;
            f[0].value = -1;
            g[0].value = -1;

            //a - 가장 작은 행렬일 때 처리
            a[0].row = 4;
            a[0].col = 4;
            a[0].value = 5;

            a[1].row = 0;
            a[1].col = 0;
            a[1].value = 5;

            a[2].row = 1;
            a[2].col = 1;
            a[2].value = -2;

            a[3].row = 2;
            a[3].col = 1;
            a[3].value = -1;

            a[4].row = 3;
            a[4].col = 0;
            a[4].value = 7;

            a[5].row = 3;
            a[5].col = 2;
            a[5].value = 4;

            sortingSparseMatrix(a);
            deleteDuplicateData(a);

            //b 큰크기의 행렬 처리
            b[0].row = 8;
            b[0].col = 10;
            b[0].value = 8;

            b[1].row = 0;
            b[1].col = 1;
            b[1].value = 23;

            b[2].row = 1;
            b[2].col = 5;
            b[2].value = -7;

            b[3].row = 1;
            b[3].col = 7;
            b[3].value = 8;

            b[4].row = 2;
            b[4].col = 0;
            b[4].value = 4;

            b[5].row = 2;
            b[5].col = 5;
            b[5].value = 12;

            b[6].row = 3;
            b[6].col = 4;
            b[6].value = -11;

            b[7].row = 7;
            b[7].col = 5;
            b[7].value = 9;


            b[8].row = 7;
            b[8].col = 9;
            b[8].value = -20;

            sortingSparseMatrix(b);
            deleteDuplicateData(b);

            //c - 0이 아닌 원소가 모두 음수인 행렬
            c[0].row = 9;
            c[0].col = 5;
            c[0].value = 9;

            c[1].row = 0;
            c[1].col = 1;
            c[1].value = -4;

            c[2].row = 0;
            c[2].col = 4;
            c[2].value = -2;

            c[3].row = 1;
            c[3].col = 2;
            c[3].value = -4;

            c[4].row = 3;
            c[4].col = 0;
            c[4].value = -9;

            c[5].row = 3;
            c[5].col = 2;
            c[5].value = -11;

            c[6].row = 4;
            c[6].col = 1;
            c[6].value = -1;

            c[7].row = 6;
            c[7].col = 1;
            c[7].value = -100;

            c[8].row = 7;
            c[8].col = 4;
            c[8].value = -121;

            c[9].row = 8;
            c[9].col = 4;
            c[9].value = -225;

            sortingSparseMatrix(c);
            deleteDuplicateData(c);

            //모두 음수인 행렬
            d[0].row = 4;
            d[0].col = 5;
            d[0].value = 20;

            for(int i=1;i<=d[0].value;i++) {
                d[i].row = (i-1)%d[0].row;
            }

            for(int i=1;i<= d[0].value;i++) {
                d[i].col = (i-1)%d[0].col;
            }

            for(int i=1;i<=d[0].value;i++) {
                d[i].value = -i;
            }

            sortingSparseMatrix(d);
            deleteDuplicateData(d);


            //0이 아닌 원소가 모두 양수인 행렬
            e[0].row = 6;
            e[0].col = 4;
            e[0].value = 5;

            e[1].row = 0;
            e[1].col = 0;
            e[1].value = 7;

            e[2].row = 0;
            e[2].col = 3;
            e[2].value = 3;

            e[3].row = 1;
            e[3].col = 2;
            e[3].value = 2;

            e[4].row = 4;
            e[4].col = 1;
            e[4].value = 8;

            e[5].row = 5;
            e[5].col = 3;
            e[5].value = 25;

            sortingSparseMatrix(e);
            deleteDuplicateData(e);

            //모두 양수인 행렬
            f[0].row = 5;
            f[0].col = 7;
            f[0].value = 35;

            for(int i=1;i<=f[0].value;i++) {
                f[i].row = (i-1)%f[0].row;
            }

            for(int i=1;i<= f[0].value;i++) {
                f[i].col = (i-1)%f[0].col;
            }

            for(int i=1;i<=f[0].value;i++) {
                f[i].value = i;
            }

            sortingSparseMatrix(f);
            deleteDuplicateData(f);

            //value가 없는 행렬
            g[0].row = 4;
            g[0].col = 6;
            g[0].value = 0;

            sortingSparseMatrix(g);
            deleteDuplicateData(g);


            printf("\n\n\n\t첫 번째 행렬 \n");
            transposeAndPrintTwoWay(a, a_transposed);

            printf("\n\n\n\t두 번째 행렬 \n");
            transposeAndPrintTwoWay(b, b_transposed);

            printf("\n\n\n\t세 번째 행렬 \n");
            transposeAndPrintTwoWay(c, c_transposed);

            printf("\n\n\n\t네 번째 행렬 \n");
            transposeAndPrintTwoWay(d, d_transposed);

            printf("\n\n\n\t다섯 번째 행렬 \n");
            transposeAndPrintTwoWay(e, e_transposed);

            printf("\n\n\n\t여섯 번째 행렬 \n");
            transposeAndPrintTwoWay(f, f_transposed);

            printf("\n\n\n\t일곱 번째 행렬 \n");
            transposeAndPrintTwoWay(g, g_transposed);
        }
        else {
            printf("\t! 데이터가 랜덤으로 입력됩니다.\n");
            makeRandomSparseMatrix(a);
            transposeAndPrintTwoWay(a, a_transposed);
        }
    }
}

void transposeAndPrintTwoWay(term a[], term b[]) {
    printf("\n\n\n\t 입력된 행렬입니다. \n");
    printMatrix_RepresentationOfSparseMatrix(a);
    printMatrix(a);
    fastTranspose(a, b);

    printf("\n\n\n\t Transpose된 행렬입니다. \n");
    printMatrix_RepresentationOfSparseMatrix(b);
    printMatrix(b);
}

void makeRandomSparseMatrix(term a[]) {
    //printf("make \t");
    a[0].row = rand() % (MAX_COL + 1 - 4) + 4; //최소 크기 4 보장
    printf("row : %d \t", a[0].row);
    a[0].col = rand() % (MAX_COL + 1 - 4) + 4; //최소 크기 4 보장
    printf("col : %d \t", a[0].col);
    a[0].value = rand() % ((a[0].row * a[0].col) / 3); //sparse 한 메트릭스를 위해 none zero element의 개수를 (3분의 1)이하로 랜덤 생성
    printf("value : %d \n", a[0].value);

    for (int i = 1; i <= a[0].value; i++) {
        a[i].row = rand() % a[0].row;
        a[i].col = rand() % a[0].col;
        a[i].value = rand() % 101 - 50; // -50~50
    }

    sortingSparseMatrix(a);
    deleteDuplicateData(a);
}

void makeSparseMatrix(term a[]) {
    int row, col, value;

    printf("\n\t spase 행렬의 row, col, value 입력 : ");
    scanf("%d %d %d", &row, &col, &value);

    if (row < 4) row = 4;
    if (col < 4) col = 4;
    if (row > MAX_ROW) row = MAX_ROW;
    if (col > MAX_COL) col = MAX_COL;
    if (value > 100) value = 100;
    if (value < 0) value = 0;
    if (value > row * col) value = row * col;

    printf("\n \t * 현재 행렬의 row, col, value : %d, %d, %d \n", row, col, value);

    a[0].row = row;
    a[0].col = col;
    a[0].value = value;

    for (int i = 1; i <= a[0].value; i++) {
        printf("\t %d번 Element의 row, col, value 입력 : ", i);
        scanf("%d %d %d", &a[i].row, &a[i].col, &a[i].value);

        if (a[i].row >= row || a[i].col >= col || a[i].row < 0 || a[i].col < 0) {
            printf("\n잘못된 입력입니다. 다시 입력하세요.\n");
            i--;
            continue;
        }
    }

    sortingSparseMatrix(a);
    deleteDuplicateData(a);
}

void makeDefaultMatrix(term a[]){
    int matrix[MAX_ROW][MAX_COL] = {0,};
    int row, col, value = 1;

    printf("\n\t sparse 행렬의 row, col 입력 : ");
    scanf("%d %d", &row, &col);

    if (row < 4) row = 4;
    if (col < 4) col = 4;
    if (row > MAX_ROW) row = MAX_ROW;
    if (col > MAX_COL) col = MAX_COL;


    printf("\n \t * 현재 행렬의 row, col : %d, %d \n", row, col);

    a[0].row = row;
    a[0].col = col;

    for (int i = 0; i < a[0].row; i++) {
        for (int j = 0; j < a[0].col; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < a[0].row; i++) {
        for (int j = 0; j < a[0].col; j++) {
            if(matrix[i][j] != 0){
                a[value].row = i;
                a[value].col = j;
                a[value].value = matrix[i][j];
                value++;
            }
        }
    }
    a[0].value = value-1;

    sortingSparseMatrix(a);
    deleteDuplicateData(a);
}

void deleteDuplicateData(term a[]) {
    //하는 김에 중복 데이터 없애는 처리도 했습니다. (행과 열이 같은데 value가 다른 경우, 뒤에 입력된 정보가 우선되어 수정됨)
    //정렬되지 않은 sparse matrix 도 중복을 제거할 수 있게 짰습니다.

    if(a[0].value == 0){
        return;
    }

    for (int i = 1; i < a[0].value; i++) {
        if (a[i].value == 0) {
            for (int m = i; m < a[0].value; m++) {
                a[m] = a[m + 1];
            }
            a[0].value--;
            i--;
            continue;
        }
        for (int j = i + 1; j <= a[0].value; j++) {
            if (a[i].row == a[j].row && a[i].col == a[j].col) {
                a[i].value = a[j].value;
                for (int m = j; m < a[0].value; m++) {
                    a[m] = a[m + 1];
                }
                j--;
                a[0].value--;
            }
        }
    }

    //마지막이 value가 0이면 제거하는 코드 (위에서 i가 a[0].value-1 일때 까지만 0인 것을 제외하기 때문에.
    if (a[a[0].value].value == 0) {
        a[0].value--;
    }
}

void fastTranspose(term a[], term b[]) {
    if (a[0].value == -1) {
        printf("\t행렬에 데이터가 없습니다.\n");
        return;
    }

    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < numCols; i++) {
            rowTerms[i] = 0;
        }
        for (i = 1; i <= numTerms; i++) {
            rowTerms[a[i].col]++;
        }
        startingPos[0] = 1;
        for (i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        //  /* #version 03 minusPos를 정의하여 startingPos를 조정하는 방식
        int minusPos[MAX_COL] = { 0 };

        for (i = 1; i <= numTerms; i++) {
            if (a[i].value < 0) {
                minusPos[a[i].col]++;
                b[0].value--;
            }
        }
        for (i = 1; i < numCols; i++) {             // startingPos은 앞에서 한 칸 당겨지면 뒤에서도 모두 한 칸씩 당겨져야 함.
            startingPos[i] -= minusPos[i-1];
            minusPos[i] += minusPos[i-1];
        }
        for (i = 1; i <= numTerms; i++) {
            if (a[i].value > 0) {
                j = startingPos[a[i].col]++;
                b[j].row = a[i].col;
                b[j].col = a[i].row;
                b[j].value = a[i].value;
            }
        }
            // */

        /* #version 02 새롭게 startingPos를 구하는 방법. 교수님께서 지양하라고 말씀하신 방법이라 폐기
        for (i = 1; i <= numTerms; i++) {
            if (a[i].value < 0) {
                rowTerms[a[i].col]--;
                b[0].value--;
            }
        }
        for (i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        for (i = 1; i <= numTerms; i++) {
            if (a[i].value > 0) {
                j = startingPos[a[i].col]++;
                b[j].row = a[i].col;
                b[j].col = a[i].row;
                b[j].value = a[i].value;
            }
        }//*/

        /* #version 01 - Lagacy (4월 5일 이전 작성 버전) - shift를 이용하였음.
        for (i = 1; i <= numTerms; i++) {

            if (a[i].value < 0) {
                for (int m = startingPos[a[i].col]; m < b[0].value; m++) {//a[i].col뒤에 이미 들어간 term들을 다 한 칸씩 땡겨줘야함
                    b[m] = b[m + 1];
                }
                for (int n = a[i].col + 1; n < numCols; n++) { //startingPos 도 a[i].col 이후 것들은 1칸씩 다 땡겨주기
                    startingPos[n]--;
                }
                b[0].value--; //value 값 한개를 줄이기
            } else {
                j = startingPos[a[i].col]++;
                b[j].row = a[i].col;
                b[j].col = a[i].row;
                b[j].value = a[i].value;
            }


        }*/



    }

    printf("\n\n \t! Trasnpose 되었습니다.\n\n");
}

//수정되지 않은 fastTranspose를 두 번 이용하면, 정렬 된다는 사실을 인지하고 활용함.
void sortingSparseMatrix(term a[]){
    term a_transposed[MAX_TERMS];
    fastTranspose_lagacy(a, a_transposed);
    fastTranspose_lagacy(a_transposed, a);
}

void fastTranspose_lagacy(term a[], term b[]) {
    if (a[0].value == -1) {
        printf("\t행렬에 데이터가 없습니다.\n");
        return;
    }

    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < numCols; i++) {
            rowTerms[i] = 0;
        }
        for (i = 1; i <= numTerms; i++) {
            rowTerms[a[i].col]++;
        }
        startingPos[0] = 1;
        for (i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }
        for (i = 1; i <= numTerms; i++) {

            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void printMatrix_RepresentationOfSparseMatrix(term a[]) {
    if (a[0].value == -1) {
        printf("\t행렬에 데이터가 없습니다.\n");
        return;
    }
    printf("\n");
    printf("\t Print Representation Of Sparse Matrix \n");
    printf("\t--------------------------------- \n");
    printf("\t| i \t| row \t| col \t| value\t| \n");
    printf("\t--------------------------------- \n");
    for (int i = 0; i <= a[0].value; i++) {
        printf("\t| %d \t| %d \t| %d \t| %d \t| \n", i, a[i].row, a[i].col, a[i].value);
    }
    printf("\t--------------------------------- \n");
}

void printMatrix(term a[]) {
    if (a[0].value == -1) {
        printf("\t행렬에 데이터가 없습니다.\n");
        return;
    }

    int matrix[MAX_ROW][MAX_COL] = {0,};

    for (int n = 1; n <= a[0].value; n++) {
        matrix[a[n].row][a[n].col] = a[n].value;
    }

    printf("\n");
    printf("\t Print Matrix \n");
    printf("\t");
    for (int i = 0; i < a[0].col; i++) {
        printf("--------");
    }
    printf("-\n");

    for (int i = 0; i < a[0].row; i++) {
        printf("\t|");
        for (int j = 0; j < a[0].col; j++) {
            printf(" %d\t|", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\t");
    for (int i = 0; i < a[0].col; i++) {
        printf("--------");
    }
    printf("-\n");
}
