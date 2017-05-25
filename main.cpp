#include <stdio.h>

#define PROCESS_SHCEDULING_MAX 12
#define PAGE_TABLE_MAX 3

int PageTableIsNULL(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aFront, int anI);    //ҳ���Ƿ�Ϊ��
int PageTableIsHit(int aPage_Table[][PROCESS_SHCEDULING_MAX], int anI, int aProcessNum);    //ҳ���Ƿ�����
void OutPutProcessScheduling(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aProcess_Scheduling[], char aPage_Table_Flag[], int aPage_Table_Hit_Count);

int main(){
    //���̵�������
    int process_scheduling[PROCESS_SHCEDULING_MAX] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    //ҳ��
    int page_table[PAGE_TABLE_MAX][PROCESS_SHCEDULING_MAX];
    //ҳ���ʼΪ��
    page_table[0][0] = 0;
    page_table[1][0] = 0;
    page_table[2][0] = 0;
    //ҳ���Ƿ����У�'N'��ʾȱҳ��'Y'��ʾ����
    char page_table_flag[PROCESS_SHCEDULING_MAX];
    //FIFO���ף�����ҳ�������Խṹ��ÿ����ҳ���û���front = (front + 1) % PAGE_TABLE_MAX
    int front = 0;
    int page_table_hit_count = 0;

    for(int i = 0; i < PROCESS_SHCEDULING_MAX; i++){
        //���̵���
        //������У�����ҳ����Ϣ
        if(!PageTableIsHit(page_table, i, process_scheduling[i])){
            //page_table[front][i] = process_scheduling[i];
            page_table_flag[i] = 'Y';
            page_table_hit_count++;
        }
        //δ���У�����ȱҳ�ж�
        else{
            //��������������֧������ͬ�������ʲ�ͬ��if�еı�ʾ���ҳ��д����Ϣ����else�еı�ʾ����ҳ�������̭��д���½���
            //����п���ҳ�������ҳ����Ϣ
            if(!PageTableIsNULL(page_table, front, i))
                page_table[front][i] = process_scheduling[i];
            //�޿���ҳ���FIFO�����㷨
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
    //����ǵ�һ�ν��̵���
    if(0 == anI) return 0;
    //���Ϊ�շ���0�����򷵻�1
    return (0 == aPage_Table[aFront][anI - 1] ? 0 : 1);
}

int PageTableIsHit(int aPage_Table[][PROCESS_SHCEDULING_MAX], int anI, int aProcessNum){
    //����ǵ�һ�ν��̵���
    if(0 == anI) return 1;
    //���Ϊ���з���0�����򷵻�1
    for(int i = 0; i < PAGE_TABLE_MAX; i++){
        if(aProcessNum == aPage_Table[i][anI-1]){
            return 0;
        }
        else{}
    }
    return 1;
}

void OutPutProcessScheduling(int aPage_Table[][PROCESS_SHCEDULING_MAX], int aProcess_Scheduling[], char aPage_Table_Flag[], int aPage_Table_Hit_Count){
    printf("���̵������м�ҳ������㷨��N��ʾδ���У�Y��ʾ���У���\n");
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
    printf("ȱҳ�� = %.2f%%\n", (PROCESS_SHCEDULING_MAX - aPage_Table_Hit_Count) * 100.0 / PROCESS_SHCEDULING_MAX);
    printf("========================================\n");
}
