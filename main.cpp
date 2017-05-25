#include <stdio.h>

#define PROCESS_SHCEDULING_MAX 12
#define PAGE_TABLE_MAX 3

int PageTableIsNULL(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aFront, int anI);    //页表是否为空
int PageTableIsHit(int aPage_Table[][PROCESS_SHCEDULING_MAX], int anI, int aProcessNum);    //页表是否命中
void OutPutProcessScheduling(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aProcess_Scheduling[], char aPage_Table_Flag[], int aPage_Table_Hit_Count);

int main(){
    //进程调度序列
    int process_scheduling[PROCESS_SHCEDULING_MAX] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    //页表
    int page_table[PAGE_TABLE_MAX][PROCESS_SHCEDULING_MAX];
    //页表初始为空
    page_table[0][0] = 0;
    page_table[1][0] = 0;
    page_table[2][0] = 0;
    //页表是否被命中，'N'表示缺页，'Y'表示命中
    char page_table_flag[PROCESS_SHCEDULING_MAX];
    //FIFO队首，由于页表是线性结构，每发生页面置换，front = (front + 1) % PAGE_TABLE_MAX
    int front = 0;
    int page_table_hit_count = 0;

    for(int i = 0; i < PROCESS_SHCEDULING_MAX; i++){
        //进程调度
        //如果命中，更新页表信息
        if(!PageTableIsHit(page_table, i, process_scheduling[i])){
            //page_table[front][i] = process_scheduling[i];
            page_table_flag[i] = 'Y';
            page_table_hit_count++;
        }
        //未命中，发生缺页中断
        else{
            //下面两个条件分支语句块相同，但本质不同，if中的表示向空页表写入信息，而else中的表示对满页表进行淘汰并写入新进程
            //如果有空余页表项，更新页表信息
            if(!PageTableIsNULL(page_table, front, i))
                page_table[front][i] = process_scheduling[i];
            //无空余页表项，FIFO调度算法
            else{
                page_table[front][i] = process_scheduling[i];
            }
            page_table_flag[i] = 'N';
            front = (front + 1) % 3;
        }
        if(i < PROCESS_SHCEDULING_MAX - 1){
            page_table[0][i+1] = page_table[0][i];
            page_table[1][i+1] = page_table[1][i];
            page_table[2][i+1] = page_table[2][i];
        }
    }

    OutPutProcessScheduling(page_table, process_scheduling, page_table_flag, page_table_hit_count);
    return 0;
}

int PageTableIsNULL(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aFront, int anI){
    //如果是第一次进程调度
    if(0 == anI) return 0;
    //如果为空返回0，否则返回1
    return (0 == aPage_Table[aFront][anI - 1] ? 0 : 1);
}

int PageTableIsHit(int aPage_Table[][PROCESS_SHCEDULING_MAX], int anI, int aProcessNum){
    //如果是第一次进程调度
    if(0 == anI) return 1;
    //如果为命中返回0，否则返回1
    for(int i = 0; i < PAGE_TABLE_MAX; i++){
        if(aProcessNum == aPage_Table[i][anI-1]){
            return 0;
        }
        else{}
    }
    return 1;
}

void OutPutProcessScheduling(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aProcess_Scheduling[], char aPage_Table_Flag[], int aPage_Table_Hit_Count){
    printf("进程调度序列及页面调度算法（N表示未命中，Y表示命中）：\n");
    printf("========================================\n");
    printf(" ");
    for(int i = 0; i < PROCESS_SHCEDULING_MAX; i++)
        printf("  %d", aProcess_Scheduling[i]);
    printf("\n");
    printf("\n");
    for(int i = 0; i < PAGE_TABLE_MAX; i++){
        printf("0");
        for(int j = 0; j < PROCESS_SHCEDULING_MAX; j++)
            printf("  %d", aPage_Table[i][j]);
        printf("\n");
    }
    printf(" ");
    for(int i = 0; i < PROCESS_SHCEDULING_MAX; i++)
        printf("  %c", aPage_Table_Flag[i]);
    printf("\n");
    printf("缺页率 = %.2f%%\n", (PROCESS_SHCEDULING_MAX - aPage_Table_Hit_Count) * 100.0 / PROCESS_SHCEDULING_MAX);
    printf("========================================\n");
}
