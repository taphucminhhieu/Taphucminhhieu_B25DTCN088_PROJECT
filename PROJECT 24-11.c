#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BOOK 1000
#define ITEMS_PER_PAGE 10
#define MAX_BORROW 1000

void display_menu();
void input_book();
void display_book();
void delete_book();
void search_book();
void clean_input_buffer();
void add_borrow();
void update_book();
void return_book();
void display_borrows();
void initialize_data();

int totalBooks;
int book_count;
int choice;
int id =1;
int idBookExisted();
int borrow_count =0; 
int borrow_id = 1; 
int n_book;
int idBookExisted(int check_id);



int is_leap(int year);
typedef struct{ 
	int day;   
	int month;
	int year;
}Date;

typedef struct { 
    int bookId;    
    char title [50]; 
    char author [50];
    int publishYear; 
    int quantity;   
}Book;

typedef struct {
	int borrowld;       
	int bookld;        
	Date borrowDate;      
	Date borrowReturn;   
	char borrowerName[50];
	int status;          
}Borrow;


Book books [MAX_BOOK];  
Borrow borrows [MAX_BORROW];
   

void clean_input_buffer() {
    int c;
        c = fflush(stdin);
    while ((c = getchar()) != '\n' && c != EOF);
}

int is_title_existed(char title[]) {
	int i;
    for ( i = 0; i < book_count; i++) {
        if (strcmp(books[i].title, title) == 0) {
            return i; 
        }
    }
    return -1;
}

int is_already_borrowed_by_name(int book_id, char name[]) {
	int i;
    for ( i = 0; i < borrow_count; i++) {
        if (borrows[i].bookld == book_id &&
            strcmp(borrows[i].borrowerName, name) == 0 &&
            borrows[i].status == 1) 
        {
            return 1; 
        }
    }
    return 0;
}
int is_leap(int y) {
    return (y%400==0) || (y%4==0 && y%100!=0);
}

int is_valid_date(Date d) {
    if (d.year < 1900 || d.year > 3000) return 0;
    if (d.month < 1 || d.month > 12) return 0;

    int maxDay;
    switch (d.month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxDay = 31; break;
        case 4: case 6: case 9: case 11:
            maxDay = 30; break;
        case 2:
            maxDay = is_leap(d.year) ? 29 : 28;
            break;
    }

    return (d.day >= 1 && d.day <= maxDay);
}

int compare_dates(Date a, Date b) {
    if (a.year != b.year) return a.year - b.year;
    if (a.month != b.month) return a.month - b.month;
    return a.day - b.day;
}

int findBorrowIndexById(int borrow_id) {
    int i;
	for (i = 0; i < borrow_count; i++) {
        if (borrows[i].borrowld == borrow_id) {
            return i;
        }
    }
    return -1;
}

void dispaly_book_info(Book s , int index) {
	printf(" Ma sach: %d\n",s.bookId);                  
	printf(" Tieu de sach: %s\n",s.title);               
	printf(" Ten tac gia: %s\n",s.author);               
	printf(" Nam xuat ban: %d\n",s.publishYear);         
	printf(" so luong sach trong kho : %d\n",s.quantity); 

}

void initialize_data() {
	int i;
Book sample_books[]={
        {0,"Nha gia kim","Paulo Coelho",1988,5},
        {1,"Toan hoc A1","Nguyen Van A",2020,10},
        {2,"Lap trinh C co ban","Pham Thi B",2022,12},
        {3,"Tieng Anh 1","Le Van C",2018,8},
        {4,"Vat Ly 10","Tran Thi D",2019,7},
        {5,"Hoa Hoc 11","Nguyen Van E",2017,9},
        {6,"Sinh Hoc 12","Pham Thi F",2021,11},
        {7,"Lich Su Viet Nam","Le Thi G",2016,6},
        {8,"Dia Ly 10","Tran Van H",2015,10},
        {9,"GDCD 11","Nguyen Thi I",2020,5},        
        {10,"Lap trinh Python","Tran Thi L",2022,12},
        {11,"Lap trinh Java","Nguyen Van M",2021,9},
        {12,"Kinh te hoc","Pham Thi N",2019,7},
        {13,"Quan tri kinh doanh","Le Van O",2020,6},
        {14,"Marketing co ban","Tran Thi P",2018,8},
        {15,"Co khi dong","Nguyen Van Q",2022,10},
        {16,"Dien tu co ban","Pham Thi R",2021,9},
        {17,"Thiet ke do hoa","Le Van S",2023,5}
    };
    int n=sizeof(sample_books)/sizeof(Book);
    for(i=0;i<n;i++){
        books[book_count].bookId = id++;
        strcpy(books[book_count].title, sample_books[i].title);
        strcpy(books[book_count].author, sample_books[i].author);
        books[book_count].publishYear = sample_books[i].publishYear;
        books[book_count].quantity = sample_books[i].quantity;
        book_count++;
    }
}

int main () {
	initialize_data();
	do{
		display_menu(); 
		if (scanf("%d",&choice) !=1) { 
			printf("\nLua chon khong hop le. Vui long nhap lai lua chon. \n");
			while(getchar() != '\n' && getchar() != EOF);
			continue; 
		} 
		
		switch (choice) { 
		case 1:
			input_book(); 
			break;
		case 2:
			update_book();
			break;
		case 3:
			display_book();
			break;
		case 4:
			delete_book();
			break;
		case 5:
			search_book();
			break;
		case 6:
			add_borrow();
			break;
		case 7:
			return_book();
			break;
		case 8:
			display_borrows();
			break;
		case 0: 
		    printf("\n   ket thuc chuong trinh. Tam biet!   ");
		    break;
		default : 
		    printf("lua chon khong hop le. vui long lua chon lai");
		    break;
		}
	}while (choice !=0 ); 
	return 0;
}

void display_menu() {
    printf("\n===================================\n");
    printf("  CHUONG TRINH QUAN LY THU VIEN \n");
    printf("___________________________________\n");
    printf("|1. Them sach moi.                |\n");
    printf("|2. Cat nhat thong tin sach.      |\n");
    printf("|3. Hien thi danh sach sach.      |\n");
    printf("|4. Xoa thong tin sach.           |\n");
    printf("|5. Tim kiem sach.                |\n");
    printf("|6. Them moi phieu muon.          |\n");
    printf("|7. Tra sach.                     |\n");
    printf("|8. Hien thi danh sach phieu muon.|\n");
    printf("|0. Thoat.                        |\n");
	printf("|_________________________________|\n");
    printf("Chon chuc nang (0-8): ");

}

void input_book () { 
	if(book_count >= MAX_BOOK){ 
		printf("\n so luong sach bi day. khong the luu tru them sach moi. \n");
		return ; 
	}
	printf("\n -----------Nhap thong tin sach-------------\n");
	
	books[book_count].bookId = id;
	printf("Ma sach: %d\n",id);
	
	do 
	{
	printf("Tieu de sach: ");
	getchar(); 
	fgets(books[book_count].title,50,stdin);
	books[book_count].title[ strcspn (books[book_count].title, "\n")] = 0;
	
	if(strlen(books[book_count].title) == 0){
		printf("vui long nhap lai tieu de sach\n");
	}else if( is_title_existed(books[book_count].title) != -1) { 
		    printf("Loi: Tieu de sach da ton tai . \n");
			books[book_count].title[0] = '\0';
		   books[book_count].title[0] = '\0';
		   continue; 
		}
	}while(strlen(books[book_count].title) ==0);
	
	do 
	{
	printf("Ten tac gia: ");
	fgets(books[book_count].author,50,stdin);
	books[book_count].author[ strcspn (books[book_count].author, "\n")] = 0;
	
	if (strlen(books[book_count].author) == 0) {
	        printf("Vui long nhap lai ten tac gia.\n");
	    }
	}while (strlen(books[book_count].author) == 0);
	
	 int statusY=0;
        char lastCharY=0;
      do {
            printf("Nhap nam xuat ban: ");
          statusY= scanf("%d",&books[book_count].publishYear);
           lastCharY= getchar();
            fflush(stdin);
        if (books[book_count].publishYear<1900 || books[book_count].publishYear > 2025) {
            printf("Nam khong hop le!!!\n");
            printf("Them sach that bai\n");
        }else {
            if (statusY == 0 || lastCharY != '\n') {
                printf("Nhap so nguyen cua nam\n");
                printf("Them sach that bai\n");
            }
        }
    }while (books[book_count].publishYear<1900 || books[book_count].publishYear > 2025 || statusY == 0 || lastCharY != '\n');

	int statusQ=0;
        char lastCharQ=0;
        do{
	printf("So luong con trong kho: ");
	statusQ = scanf("%d", &books[book_count].quantity);
	lastCharQ = getchar();
	fflush(stdin);
	if (books[book_count].quantity <0 || books[book_count].quantity> MAX_BOOK){
		printf("So luong xuat ban khong hop le!!\n");
		printf("Them so luong sach khong thanh cong\n");
	}else {
		if(statusQ ==0 || lastCharY != '\n'){
			printf("Nhap so nguyen cua sach\n");
			printf("Them so luong sach that bai\n");
		}
	}
    	}while(statusQ == 0 || lastCharQ != '\n' || books[book_count].quantity<0 || books[book_count].quantity >MAX_BOOK );

	
	book_count++; 
	printf("Da them sach %s thanh cong. \n", books[book_count-1].title);
	id++; 
}

void update_book() {
    int id_find;
    int target_index;

    if (book_count == 0) {
        printf(" Khong the cap nhat.\n");
        return;
    }

    do {
        printf("\nNhap ma sach can cap nhat: ");
        if (scanf("%d", &id_find) != 1) {
            printf("Ma sach khong hop le. Vui long nhap lai.\n");
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }
        while (getchar() != '\n' && getchar() != EOF);

        target_index = idBookExisted(id_find);
        if (target_index == -1) {
            printf("Khong tim thay sach co ma ID %d.\n", id_find);
        }
    } while (target_index == -1);

    printf("Tim thay sach. Nhap thong tin moi:\n");
    int i = target_index;

    do
    {
        printf("Tieu de sach: ");
        fgets(books[i].title,50,stdin);
        books[i].title[ strcspn (books[i].title, "\n")] = 0;

        if(strlen(books[i].title) == 0){
            printf("vui long nhap lai tieu de sach\n");
        }
    }while(strlen(books[i].title) ==0);


    do
    {
        printf("Ten tac gia: ");
        fgets(books[i].author,50,stdin);
        books[i].author[ strcspn (books[i].author, "\n")] = 0;

        if (strlen(books[i].author) == 0) {
            printf("Vui long nhap lai ten tac gia.\n");
        }
    }while (strlen(books[i].author) == 0);


    int statusY = 0;
    char lastCharY = 0;
    do {
        printf("Nam xuat ban moi : ");
        if ((statusY = scanf("%d", &books[i].publishYear)) == 1) {
            lastCharY = getchar();
        } else {
            while (getchar() != '\n' && getchar() != EOF);
            lastCharY = 0;
        }

        if (statusY == 0 || lastCharY != '\n') {
            printf("Nhap so nguyen cua nam. Vui long nhap lai.\n");
        } else if (books[i].publishYear < 1900 || books[i].publishYear > 2025) {
            printf("Nam khong hop le (1900-2025)!!! Vui long nhap lai.\n");
        }
    } while (books[i].publishYear < 1900 || books[i].publishYear > 2025 || statusY == 0 || lastCharY != '\n');

    while (getchar() != '\n' && getchar() != EOF); 

    int statusQ = 0;
    char lastCharQ = 0;
    do {
        printf("So luong moi : ");
        if ((statusQ = scanf("%d", &books[i].quantity)) == 1) {
            lastCharQ = getchar();
        } else {
            while (getchar() != '\n' && getchar() != EOF);
            lastCharQ = 0;
        }

        if (statusQ != 1 || lastCharQ != '\n' || books[i].quantity <= 0) {
            printf("Vui long nhap lai so luong hop le (so nguyen duong).\n");
        }
    } while (statusQ != 1 || lastCharQ != '\n' || books[i].quantity <= 0);

    printf("Cap nhat thanh cong.\n");
}
   
int idBookExisted(int check_id) {
    int i;
    for (i = 0; i < book_count; i++) {
        if (books[i].bookId == check_id) {
            return i; 
        }
    }
    return -1; 
}

void display_book() {
int currentPage = 1; 
    int totalPages;     
    int choicePage;     
    int isValidInput; 
	int stt; 
	if (book_count == 0) {
		printf("\nDanh sach sach hien tai dang rong. Vui long them sach truoc.\n");
		return;
	}
    totalPages = book_count / ITEMS_PER_PAGE + (book_count % ITEMS_PER_PAGE != 0);

     do {
        int startIndex = (currentPage - 1) * ITEMS_PER_PAGE;

		int endIndex = startIndex + ITEMS_PER_PAGE;
        if (endIndex > book_count) {
            endIndex = book_count; 
        }

        printf("\n========================================================================================================\n");
        printf("                       DANH SACH SACH | TRANG %d/%d                       \n", currentPage, totalPages);
        printf("==========================================================================================================\n");

        printf("| %-5s | %-30s | %-20s | %-12s | %-8s |\n", 
            "ID", "Tieu de", "Tac gia", "Nam XB", "So luong");
        printf("----------------------------------------------------------------------------------------------------\n");

        int i;
        for (i = startIndex; i < endIndex; i++) {
            Book s = books[i]; 
            int bookId = i + 1;
            
            printf("| %-5d | %-30s | %-20s | %-12d | %-8d |\n",
                bookId, s.title, s.author, s.publishYear, s.quantity);
            
            printf("-----------------------------------------------------------------------------------------------\n");
        }
   
        printf("Tong so luong sach trong kho: %d cuon.\n", book_count);

        printf("\n[Trang %d/%d] Chon chuc nang: ", currentPage, totalPages);
        
         if (currentPage > 1) {
            printf("1. Trang truoc | ");
        }
        printf("2. Trang tiep theo | ");
        if (currentPage < totalPages) {
            printf("0. ve MENU");
        }
        printf("\n=> Nhap lua chon (1, 2, 0): ");

        isValidInput = scanf("%d", &choicePage);
        while (getchar() != '\n'); 
        if (isValidInput != 1) {
            printf("Lua chon khong hop le. Vui long nhap so nguyen.\n");
            continue; 
        }

        switch (choicePage) {
            case 1: 
                if (currentPage > 1) {
                    currentPage--;
                } else {
                    printf("Ban dang o trang dau tien.\n");
                }
                break;
            case 0:
                printf("Thoat khoi chuc nang hien thi danh sach sach.\n");
                return; 
            case 2:
                if (currentPage < totalPages) {
                    currentPage++;
                } else {
                    printf("Ban dang o trang cuoi cung.\n");
                }
                break;
            default:
                printf("Lua chon khong hop le. Quay lai Menu chinh.\n");
                return; 
        }

    } while (1); 
}

void delete_book() {
    int i;
    int j;
    int deleteId;
    int target_index;

    if (book_count == 0) {
        printf("Danh sach trong\n");
        printf("Moi ban nhap them sach\n");
        return;
    } 
    do {
        int statusI = 0;
        char lastcharI = 0;

        printf("\nNhap ma so sach ban can xoa: ");
        
        if ((statusI = scanf("%d", &deleteId)) == 1) {
            lastcharI = getchar();
        } else {
            while (getchar() != '\n' && getchar() != EOF); 
            lastcharI = 0;
        }

        if (statusI == 0 || lastcharI != '\n') {
            printf("Nhap ma so sach that bai. Vui long nhap mot so nguyen.\n");
            target_index = -1; 
            continue;
        }

        target_index = idBookExisted(deleteId);
        if (target_index == -1) {
            printf("Khong ton tai ma so sach %d trong danh sach. Vui long nhap lai.\n", deleteId);
        }

    } while (target_index == -1); 

    for (j = target_index; j < book_count - 1; j++) {
        books[j] = books[j + 1];
    }
    
    book_count--;
    printf("Da xoa sach co ma so %d thanh cong.\n", deleteId);
}

void search_book() {
    char keyword[50];
    int found_count = 0;
    int i;

    printf("\n----------- TIM KIEM SACH THEO TIEU DE -----------\n");

    if (book_count == 0) {
        printf("Danh sach sach hien tai dang rong. Khong the tim kiem.\n");
        return;
    }

    do {
        printf("Nhap tieu de sach muon tim: ");
        clean_input_buffer();
        fgets(keyword, 50, stdin);
        keyword[strcspn(keyword, "\n")] = 0; 
        
        if (strlen(keyword) == 0) {
            printf("Vui long nhap tieu de sach. Khong duoc de trong.\n");
        }
    } while (strlen(keyword) == 0);
    
    printf("\n--- Ket qua tim kiem cho: '%s' ---\n", keyword);
    printf("| %-5s | %-30s | %-20s | %-12s | %-8s |\n",
        "ID", "Tieu de", "Tac gia", "Nam XB", "So luong");
    printf("----------------------------------------------------------------------------------------------------\n");


    for (i = 0; i < book_count; i++) {
        if (strstr(books[i].title, keyword) != NULL) {
            printf("| %-5d | %-30s | %-20s | %-12d | %-8d |\n",
                books[i].bookId, books[i].title, books[i].author, books[i].publishYear, books[i].quantity);
            printf("----------------------------------------------------------------------------------------------------\n");
            
            found_count++;
        }
    }
    if (found_count == 0) {
        printf("--> Khong tim thay sach nao co tieu de chua '%s' trong danh sach.\n", keyword);
    } else {
        printf("Tim thay tong cong %d cuon sach.\n", found_count);
    }
}

void add_borrow() {
    int book_id_input;
    int book_index;
    char line[100]; 
    char confirm;
    int j;
clean_input_buffer();
    printf("\n----------- Them moi phieu muon -------------\n");
   
    if (borrow_count >= MAX_BORROW) {
        printf("\n=> THONG BAO: So luong phieu muon bi day.\n");
        return;
    }

    if (book_count == 0) {
        printf("=> THONG BAO:Danh sach sach hien tai dang rong.\n");
        return;
    }
	 	
    do {
        printf("Nhap ma sach can muon: ");

    if (!fgets(line, sizeof(line), stdin)) 
     continue;
           line[strcspn(line, "\n")] = 0;

    if (strlen(line) == 0) {
           printf("Loi: Ma sach khong duoc de trong. Vui long nhap lai.\n");
        book_index = -1;
            continue;
}

        if (sscanf(line, "%d", &book_id_input) != 1) {
            printf("Loi: Ma sach phai la so nguyen. Vui long nhap lai.\n");
            book_index = -1;
            continue;
        }

        book_index = idBookExisted(book_id_input);
        if (book_index == -1) {
            printf("Loi: Khong tim thay sach co Ma ID %d. Vui long nhap lai.\n", book_id_input);
        } else if (books[book_index].quantity <= 0) {
            printf("Loi: Sach '%s' (Ma ID %d) da het.\n", books[book_index].title, book_id_input);
            book_index = -1;
        }
    } while (book_index == -1);

    printf("\n---------------- Sach duoc chon ----------------\n");
    printf("| %-10s | %-30s | %-15s | %-10s |\n", "ID", "Tieu de", "Tac gia", "SL Kho");
    for(j = 1; j <= 73; j++) printf("-"); printf("\n");
    printf("| %-10d | %-30s | %-15s | %-10d |\n",
               books[book_index].bookId,
               books[book_index].title,
               books[book_index].author,
               books[book_index].quantity);
    for( j = 1; j <= 73; j++) printf("-"); printf("\n");
    do {
        printf("Nhap Ten nguoi muon sach: ");
        if (!fgets(borrows[borrow_count].borrowerName, sizeof(borrows[borrow_count].borrowerName), stdin))
            continue;


        size_t len = strlen(borrows[borrow_count].borrowerName);
        if (len > 0 && borrows[borrow_count].borrowerName[len - 1] == '\n') {
            borrows[borrow_count].borrowerName[len - 1] = '\0';
            len--; 
        }
        
        if (len == 0) {
            printf("Loi: Ten nguoi muon khong duoc de trong. Vui long nhap lai.\n");
        }

    } while (strlen(borrows[borrow_count].borrowerName) == 0);


    if (is_already_borrowed_by_name(book_id_input, borrows[borrow_count].borrowerName)) {
        printf("\n=> THONG BAO: Them phieu muon that bai!\n");
        printf("Loi: Nguoi muon '%s' hien dang giu cuon sach '%s' (Ma ID: %d).\n",
               borrows[borrow_count].borrowerName,
               books[book_index].title,
               book_id_input);
        printf("Vui long tra sach truoc khi muon them.\n");
        return;
    }

    do {
        printf("Ban co muon muon sach nay khong (y/n)? ");
        if (!fgets(line, sizeof(line), stdin)) continue;
        
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        if (sscanf(line, " %c", &confirm) != 1) continue;
        confirm = tolower(confirm);
        if (confirm == 'n') {
            printf("=> THONG BAO: Huy tao phieu muon.\n");
            return;
        }
    } while (confirm != 'y');

    Date borrowDate_input;
    do {
        printf("Nhap Ngay muon (dd mm yyyy): ");
        if (!fgets(line, sizeof(line), stdin)) continue;
        
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        if (sscanf(line, "%d %d %d", &borrowDate_input.day, &borrowDate_input.month, &borrowDate_input.year) != 3) {
            printf("Loi: Ngay thang khong hop le. Vui long nhap lai.\n");
            continue;
        }
        if (!is_valid_date(borrowDate_input)) {
            printf("Loi: Ngay muon khong hop le. Vui long nhap lai.\n");
        }
    } while (!is_valid_date(borrowDate_input));

    Date borrowReturn_input;
    do {
        printf("Nhap Ngay tra du kien (dd mm yyyy): ");
        if (!fgets(line, sizeof(line), stdin)) continue;

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        if (sscanf(line, "%d %d %d", &borrowReturn_input.day, &borrowReturn_input.month, &borrowReturn_input.year) != 3) {
            printf("Loi: Ngay thang khong hop le. Vui long nhap lai.\n");
            continue;
        }
        if (!is_valid_date(borrowReturn_input) ||
            compare_dates(borrowReturn_input, borrowDate_input) <= 0) {
            printf("Loi: Ngay tra du kien phai sau Ngay muon. Vui long nhap lai.\n");
        }
    } while (!is_valid_date(borrowReturn_input) || compare_dates(borrowReturn_input, borrowDate_input) <= 0);

    borrows[borrow_count].borrowld = borrow_id;
    borrows[borrow_count].bookld = book_id_input;
    borrows[borrow_count].borrowDate = borrowDate_input;
    borrows[borrow_count].borrowReturn = borrowReturn_input;
    borrows[borrow_count].status = 1;

    books[book_index].quantity--;
    borrow_count++;
    borrow_id++;

    printf("\n==> THONG BAO: Them phieu muon thanh cong!\n");
    printf("- Ma phieu: %d\n", borrows[borrow_count - 1].borrowld);
    printf("- Sach: %s (Ma ID: %d)\n- So luong con lai: %d\n",
               books[book_index].title, book_id_input, books[book_index].quantity);
    printf("- Ngay muon: %d/%d/%d\n", borrowDate_input.day, borrowDate_input.month, borrowDate_input.year);
    printf("- Ngay tra du kien: %d/%d/%d\n", borrowReturn_input.day, borrowReturn_input.month, borrowReturn_input.year);
}

void return_book() {
    int return_id, idx;

    if (borrow_count == 0) {
        printf("\nHien tai khong co phieu muon nao.\n");
        return;
    }

    printf("\n--- CHUC NANG TRA SACH ---\n");

    do {
        printf("Nhap MaPhieu muon can tra (hoac 0 de huy): ");
        if (scanf("%d", &return_id) != 1) {
            clean_input_buffer();
            printf("Nhap khong hop le. Vui long nhap lai.\n");
            continue;
        }
        clean_input_buffer();

        if (return_id == 0) {
            printf("Huy thao tac tra sach.\n");
            return;
        }

        idx = findBorrowIndexById(return_id);
        if (idx == -1) {
            printf("MaPhieu %d khong ton tai. Vui long nhap lai.\n", return_id);
        } else if (borrows[idx].status == 0) {
            printf("Phieu %d da duoc tra truoc do.\n", return_id);
            idx = -1;
        }

    } while (idx == -1);

    Date return_date;
    int status_read;
    do {
        printf("Nhap Ngay tra sach (dd mm yyyy): ");
        status_read = scanf("%d %d %d", &return_date.day, &return_date.month, &return_date.year);
        clean_input_buffer();

        if (status_read != 3) {
            printf("Nhap khong hop le. Vui long nhap 3 so nguyen.\n");
            continue;
        }

        if (!is_valid_date(return_date)) {
            printf("Ngay tra khong hop le. Vui long nhap lai.\n");
        } else if (compare_dates(return_date, borrows[idx].borrowDate) < 0) {
            printf("Ngay tra khong duoc nho hon ngay muon (%02d/%02d/%04d).\n",
                   borrows[idx].borrowDate.day,
                   borrows[idx].borrowDate.month,
                   borrows[idx].borrowDate.year);
        } else {
            break;
        }
    } while (1);

    borrows[idx].borrowReturn = return_date;
    borrows[idx].status = 0;

    int book_idx = idBookExisted(borrows[idx].bookld);
    if (book_idx != -1) {
        books[book_idx].quantity++;
    }

    printf("\n=> Tra sach thanh cong cho MaPhieu: %d\n", return_id);
    printf("- Nguoi muon: %s\n", borrows[idx].borrowerName);
    printf("- Sach: %s (Ma ID: %d)\n",
           (book_idx != -1) ? books[book_idx].title : "Khong tim thay ten sach ",
           borrows[idx].bookld);
    printf("- Ngay tra: %02d/%02d/%04d\n", return_date.day, return_date.month, return_date.year);
    if (book_idx != -1) {
        printf("- So luong sach hien tai trong kho: %d\n", books[book_idx].quantity);
    }
}


void display_borrows() {
	int i;
    if (borrow_count == 0) {
        printf("\nKhong co phieu muon nao!\n");
        return;
    }

    int totalPages = (borrow_count + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    int currentPage = 1;
    char ch;

    do {
        system("cls");  

        int start = (currentPage - 1) * ITEMS_PER_PAGE;
        int end = start + ITEMS_PER_PAGE;
        if (end > borrow_count) end = borrow_count;

        printf("\n===============================================================\n");
        printf("                 DANH SACH PHIEU MUON | TRANG %d/%d\n",
               currentPage, totalPages);
        printf("===============================================================\n");
        printf("| %-5s | %-10s | %-20s | %-10s | %-12s | %-12s |\n",
               "STT", "Ma phieu", "Nguoi muon", "Ma sach", "Ngay muon", "Trang thai");
        printf("--------------------------------------------------------------------------\n");

        for ( i = start; i < end; i++) {
            printf("| %-5d | %-10d | %-20s | %-10d | %02d/%02d/%04d | %-12s |\n",
                   i + 1,
                   borrows[i].borrowld,         
                   borrows[i].borrowerName,     
                   borrows[i].bookld,         
                   borrows[i].borrowDate.day,  
                   borrows[i].borrowDate.month,
                   borrows[i].borrowDate.year,
                   borrows[i].status == 0 ? "Dang muon" : "Da tra"
            );
        }

        printf("--------------------------------------------------------------------------\n");
        printf("Nhan N = trang truoc | P = trang sau | Q = thoat\n");
        printf("Nhap lua chon: ");
        fflush(stdin);
        ch = getchar();
        ch = toupper(ch);

        if (ch == 'P' && currentPage < totalPages) currentPage++;
        if (ch == 'N' && currentPage > 1) currentPage--;

    } while (ch != 'Q');
}

