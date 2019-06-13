#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 64

typedef struct RECORD{
	int id;
	char fname[LENGTH];
	char lname[LENGTH];
	char email[LENGTH];
	struct RECORD *next;
}REC;

/*プロトタイプ宣言*/

/*—与えられた関数群—*/
/*————————————————————————————————————————————————————————————————————*/
/*ReadData関数*/
REC *readdata(REC *record);
/*WriteData関数*/
REC *writedata(REC *record);
/*Add関数*/
REC *add(REC *record, char *fname, char *lname, char *email);
/*Delete関数*/
REC *delete(REC *record, int id);
/*Find関数*/
char find(REC *record);
/*Sort関数*/
REC *sort(REC *record, int type, int elect);
int judge(REC *record, REC *compare, int type, int elect);
void swap_rec(REC *record, REC *next);
/*————————————————————————————————————————————————————————————————————*/

/*—自作関数群—*/
/*————————————————————————————————————————————————————————————————————*/
/*表示するメニューを保持する関数*/
int mainmenu(REC *record);
/*ファイルの作成*/
char makefile();
/*入力保持用グローバル変数*/
char inputfname[LENGTH], inputlname[LENGTH], inputemail[LENGTH], filename[LENGTH];
/*構造体の中身をすべて表示する関数*/
int showall(REC *record);
/*IDを作成する関数*/
int makeid(REC *record);
/*終了関数*/
int EXIT(REC *record);
/*————————————————————————————————————————————————————————————————————*/

int main(){
	
	makefile();
	
	REC *record = NULL;
		
	record = readdata(record);
	
	int m = makeid(record);
	
	printf("全%d件のデータが読み込まれました\n", m);
	showall(record);

	mainmenu(record);
	
	return 0;	
}

int mainmenu(REC *record){
	int operation = 0;
	int id = 1;
	
	while(1){
		puts("—メインメニュー—");
		puts("操作を数字で入力してください");
		puts("(1:新規追加, 2:削除, 3:全表示, 4:検索, 5:ソート, etc:終了)");
		printf("> ");
		fflush(stdout);
		scanf("%d", &operation);
		
		/*新規追加*/
		if(operation == 1){
			printf("\n");
			puts("姓を入力してください");
			printf("> ");
			fflush(stdout);
			scanf("%s", inputfname);
			puts("名を入力してください");
			printf("> ");
			fflush(stdout);
			scanf("%s", inputlname);
			puts("E-メールアドレスを入力してください");
			printf("> ");
			fflush(stdout);
			scanf("%s", inputemail);
			printf("\n");
			
			record = add(record, inputfname, inputlname, inputemail);
						
			writedata(record);
			
			int fin = EXIT(record);
			if(fin == 1){
				mainmenu(record);
			}
			else if(fin == 0){
				puts("以下の内容を保存します");
				showall(record);
				record = writedata(record);
				exit(0);
			}
			else{
				puts("定義値以外が入力されたため、今までのデータを保存し、異常終了します");
				record = writedata(record);
				exit(1);
			}
		}
		/*削除*/
		else if(operation == 2){
			if(record == NULL){
				puts("ファイルに何も記入されていないか、ファイルが存在しません");
			}
			else{
				printf("\n");
				showall(record);
				puts("削除する項目をIDで指定してください");
				printf("> ");
				fflush(stdout);
				scanf("%d", &id);
				record = delete(record, id);
				printf("ID:%dは完全に削除されました\n",id);
				printf("\n");
				puts("以下のように変わりました");
				showall(record);
				writedata(record);
				
				int fin = EXIT(record);
				if(fin == 1){
					mainmenu(record);
				}
				else if(fin == 0){
					puts("以下の内容を保存します");
					showall(record);
					record = writedata(record);
					exit(0);
				}
				else{
					puts("定義値以外が入力されたため、今までのデータを保存し、異常終了します");
					record = writedata(record);
					exit(1);
				}
			}
		}
		/*全表示*/
		else if(operation == 3){
			showall(record);
			
			int fin = EXIT(record);
			if(fin == 1){
				mainmenu(record);
			}
			else if(fin == 0){
				puts("以下の内容を保存します");
				showall(record);
				record = writedata(record);
				exit(0);
			}
			else{
				puts("定義値以外が入力されたため、今までのデータを保存し、異常終了します");
				record = writedata(record);
				exit(1);
			}
		}
		/*検索*/
		else if(operation == 4){
			find(record);
			
			int fin = EXIT(record);
			if(fin == 1){
				mainmenu(record);
			}
			else if(fin == 0){
				puts("以下の内容を保存します");
				showall(record);
				record = writedata(record);
				exit(0);
			}
			else{
				puts("定義値以外が入力されたため、今までのデータを保存し、異常終了します");
				record = writedata(record);
				exit(1);
			}
		}
		/*ソート*/
		else if(operation == 5){
			if(record != NULL){
				int fig1, fig2;
				fig1 = fig2 = 0;
				printf("\n");
				puts("ソートしたい項目を選んでください");
				puts("(1:姓 2:名 3:E-メールアドレス)");
				printf("> ");
				scanf("%d", &fig1);
				fflush(stdout);
				
				printf("\n");
				puts("昇順・降順を選んでください");
				puts("(1:昇順 2:降順)");
				printf("> ");
				scanf("%d", &fig2);
				fflush(stdout);
				
				record = sort(record, fig1, fig2);
				
				puts("以下のようにソートされました");
				showall(record);
				printf("\n");
				
				int fin = EXIT(record);
				if(fin == 1){
					mainmenu(record);
				}
				else if(fin == 0){
					puts("以下の内容を保存します");
					showall(record);
					record = writedata(record);
					exit(0);
				}
				else{
					puts("定義値以外が入力されたため、今までのデータを保存し、異常終了します");
					record = writedata(record);
					exit(1);
				}
			}
		}
		else{
			int fin = EXIT(record);
			if(fin == 1){
				mainmenu(record);
			}
			else if(fin == 0){
				puts("以下の内容を保存します");
				showall(record);
				record = writedata(record);
				exit(0);
			}
			else{
				puts("定義値以外が入力されたため、今までのデータを保存し、異常終了します");
				record = writedata(record);
				exit(1);
			}
		}
	}	
	return 0;
}

char makefile(){
	int select;

	puts("————————————————————————————————————————————————————————————");
	puts("ファイルの名前を拡張子(.txt)まで含めて入力するか、デフォルトの名前「adress.txt」を使用するか選んでください");
	puts("————————————————————————————————————————————————————————————");
	printf("\n");
	puts("(1:自分で名前を決める 2:デフォルトのファイル名「address.txt」を使用する, etc:終了)");
	printf("> ");
	fflush(stdout);
	scanf("%d", &select);
	
	if(select == 1){
		puts("ファイルの名前を入力してください");
		printf("> ");
		fgets(filename, sizeof(filename), stdin);
		scanf("%s", filename);
		if(filename[0] == '\n'){
			printf("\n");
			puts("不正な入力です、最初からやり直してください");
			exit(0);
		}
	}
	else if(select == 2){
		printf("\n");
		puts("デフォルトのファイル名 「address.txt」 を使用します");
		printf("\n");
		strcpy(filename, "address.txt");
	}
	else{
		puts("定義値以外が入力されたため、終了します");
		exit(0);
	}
	return 0;
}

REC *readdata(REC *record){
	int i = 0;
	FILE *fp;
	fp = fopen(filename,"r");
	
	/*ファイルがなかった時に作成する処理*/
	if(fp == NULL){
		printf("%s は存在しません\n", filename);
		return NULL;
	}
	else{
		while(fscanf(fp, "%s %s %s", inputfname, inputlname, inputemail) != EOF){
			
			record = add(record, inputfname, inputlname, inputemail);
			
			i++;
		}
		/*何らかのエラーが出た時にNULLを返す*/
		if(i == 0){
			puts("ファイルが存在しないか、ファイルの中身が空の状態です");
			printf("\n");
			return NULL;
		}
		fclose(fp);
	}	
	return record;
}

REC *writedata(REC *record){
	FILE *outputfile;
	outputfile = fopen(filename, "w");
	/*ファイルがひらけなかった時にプログラムを異常終了させる*/
	if(outputfile == NULL){
		printf("%s を開くことができません\n", filename);
		exit(1);
	}
	while(record != NULL){
		fprintf(outputfile, "%s %s %s\n", record->fname, record->lname, record->email);
		record = record->next;
	}
	fclose(outputfile);
	return 0;
}

REC *add(REC *record, char *fname, char *lname, char *email){
	REC *lead;
	REC *item;

	lead = record;

	item = (REC*)malloc(sizeof(REC));

	strcpy(item->fname, fname);
	strcpy(item->lname, lname);
	strcpy(item->email, email);
	item->next = NULL;
	
	/*始めて追加する時のみ別処理*/
	if(record == NULL){
		record = item;
		return record;
	}

	while(record->next != NULL){
		record = record->next;
	}

	record->next = item;

	return lead;
}

REC *delete(REC *record, int id){
	REC *nxad;
	REC *lead;
	lead = record;
	
	showall(record);
	/*最初のデータのみ別処理*/
	if(record != NULL && record->id == id){
		nxad = record->next;
		free(record);
		return nxad;
	}
	while(record != NULL){
		if(record->next->id == id){
			nxad = record->next->next;
			free(record->next);
			record->next = nxad;
			return lead;
		}
		record = record->next;
	}
	printf("ID:%d は見つかりませんでした\n", id);
	return NULL;
}

int showall(REC *record){
	makeid(record);
	printf("\n");
	puts("————————————————————————————————————————————————————————————");
	while(record != NULL){
		printf("%d : %s %s %s\n", record->id, record->fname, record->lname, record->email);
		record = record->next;
	}
	puts("————————————————————————————————————————————————————————————");
	printf("\n");
	return 0;
}

char find(REC *record){
	char chr[LENGTH];
	int d = 0;
	int choice;
	printf("\n");
	puts("検索したい項目の数字を入力してください(1:姓, 2:名, 3:E-メールアドレス, etc:メインメニューへ戻る)");
	printf("> ");
	fflush(stdout);
	scanf("%d", &choice);
	
	if(choice == 1){
		printf("\n");
		puts("検索したい姓を入力してください");
		printf("> ");
		fflush(stdout);
		scanf("%s", chr);
		printf("\n");
		puts("——————————————————————————————————————————————————————————");
		while(record != NULL){
			if(strcmp(record->fname, chr) == 0){
				printf("%s %s %s\n", record->fname, record->lname, record->email);
				printf("\n");
				d++;
			}
			record = record->next;
		}
		puts("——————————————————————————————————————————————————————————");
		if(d == 0){
			printf("\n");
			printf("%sという姓は存在しません\n", chr);
			printf("\n");
		}
	}
	else if(choice == 2){
		printf("\n");
		puts("検索したい名を入力してください");
		printf("> ");
		fflush(stdout);
		scanf("%s", chr);
		while(record != NULL){
			if(strcmp(record->lname, chr) == 0){
				printf("%s %s %s\n", record->lname, record->fname, record->email);
				d++;
			}
			record = record->next;
		}
		if(d == 0){
			printf("\n");
			printf("%sという名は存在しません\n", chr);
			printf("\n");
		}
	}
	else if(choice == 3){
		printf("\n");
		puts("検索したいE-メールアドレスを入力してください");
		printf("> ");
		fflush(stdout);
		scanf("%s", chr);
		while(record != NULL){
			if(strcmp(record->email, chr) == 0){
				printf("%s %s %s\n", record->email, record->fname, record->lname);
				d++;
			}
			record = record->next;
		}
		
		printf("%d件見つかりました\n", d);
		
		if(d == 0){
			printf("\n");
			printf("%sというE-メールアドレスは存在しません\n", chr);
			printf("\n");
		}
	}
	else{
		printf("\n");
	}
	return 0;
}

REC* sort(REC *record, int elect, int type) {
    REC *first = record;
    int rec_len = makeid(record);
    
	/*バブルソート*/
    for(int i = 0; i < rec_len - 1; i++) {
        record = first;
        for(int j = 0; j < rec_len - 1; j++) {
            if(judge(record, record->next, elect, type)) {
                swap_rec(record, record->next);
            }
            record = record->next;
        }
    }

    return first;
}

/*electで姓、名、E-メールアドレスを判定し、typeで昇順、降順を判定、更にstrcmpで交換対象か判定(対象なら1、そうでないなら0を返す)*/
int judge(REC *record, REC *compare, int elect, int type) {
    if (elect == 1) {
        if(type == 1) {
            if(strcmp(record->fname, compare->fname) >= 0) {
                return 1;
            }
            return 0;
        }
        else if(type == 2) {
            if(strcmp(record->fname, compare->fname) <= 0) {
                return 1;
            }
            return 0;
        }
    }
    else if(elect == 2) {
        if(type == 1) {
            if(strcmp(record->lname, compare->lname) >= 0) {
                return 1;
            }
            return 0;
        }
        else if(type == 2) {
            if(strcmp(record->lname, compare->lname) <= 0) {
                return 1;
            }
            return 0;
        }
    }
    else if(elect == 3) {
        if(type == 1) {
            if(strcmp(record->email, compare->email) >= 0) {
                return 1;
            }
            return 0;
        }
        else if(type == 2) {
            if(strcmp(record->email, compare->email) <= 0) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

void swap_rec(REC *record, REC *next){
	int id;
    char hold_f[LENGTH];
    char hold_l[LENGTH];
    char hold_e[LENGTH];

    id = record->id;
    strcpy(hold_f, record->fname);
    strcpy(hold_l, record->lname);
    strcpy(hold_e, record->email);

    record->id = next->id;
    strcpy(record->fname, next->fname);
    strcpy(record->lname, next->lname);
    strcpy(record->email, next->email);

    next->id = id;
    strcpy(next->fname, hold_f);
    strcpy(next->lname, hold_l);
    strcpy(next->email, hold_e);
}

int makeid(REC *record){
	int id = 1;
	while(record != NULL){
		record->id = id;
		record = record->next;
		id++;
	}
	return (id - 1);
}

int EXIT(REC *record){
	char ans;
	puts("まだ編集を続けますか？ y/n で答えてください");
	printf("> ");
	scanf("%s", &ans);
	fflush(stdout);
	printf("\n");
	
	if(strcmp(&ans, "y") == 0 || strcmp(&ans, "Y") == 0){
		return 1;
	}
	else if(strcmp(&ans, "n") == 0 || strcmp(&ans, "N") == 0){
		return 0;
	}
	else{
		return 10;
	}
}
