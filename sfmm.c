#include "sfmm.h"



/*#ifdef LIFO
	#define debug(fmt,...) do{}while(0)
#else
*/

void *ptr_1; /*the pointer for init*/
void *initaddr;/*pointer for initialte*/
void *ptr_2;
void *buff;

void *free_header=NULL;


unsigned long long int INIT_MEM=4096;

unsigned long long int  a =1;

unsigned long long int ac_size;
unsigned long long int remain_size=0;
size_t sbrk_counter=0;
size_t size_total=0;
/*
* initialize your memory allocator
*/

void sf_mem_init(void){
	
initaddr = sbrk(0); /*return the address of the break*/
unsigned long addr_1 = (unsigned long) initaddr;
if(addr_1%16==0){
 	sbrk(8);
 
 
} 

}

/*
* implementation of malloc 
*/
void* sf_malloc(size_t size){
    
    unsigned long long int header = 0x0000000000000000;
    unsigned long long int free_block_info=0x0000000000000000;
   
	

   if(size > FOUR_GB){
    errno=ENOMEM;
     return NULL;
	}  


	else {
         
        if(free_header==NULL){
         printf("first\n");
        /*free header null*/
		if(size>INIT_MEM){
        printf("size>init\n");
		int result= size/INIT_MEM;
		int mod=size%INIT_MEM;

		if(mod != 0){
		  result=result+1;
		  INIT_MEM=INIT_MEM*result;

		ptr_1=sbrk(INIT_MEM);
		sbrk_counter= sbrk_counter +INIT_MEM;
		ptr_2=sbrk(0);
		}
		else{
			INIT_MEM=INIT_MEM*result;
             ptr_1=sbrk(INIT_MEM);
        sbrk_counter= sbrk_counter +INIT_MEM;
             ptr_2=sbrk(0);
		}

	    }
	    ptr_1=sbrk(INIT_MEM); /*pointer 1 point at the begining of the heap*/
	    sbrk_counter= sbrk_counter +INIT_MEM;
		ptr_2=sbrk(0);/*the pointer 2 point at the end addr*/
		/*padding*/
	    /*free header null*/
        }else{
        	ptr_1=free_header;
        	printf("not first\n");
         if(size>remain_size){
         printf("size>remain\n");

        int result= size/INIT_MEM;
		int mod=size%INIT_MEM;

		if(mod != 0){
		  result=result+1;
		  INIT_MEM=INIT_MEM*result;
		sbrk(INIT_MEM);
		sbrk_counter= sbrk_counter +INIT_MEM;
		}
		else{
			INIT_MEM=INIT_MEM*result;
             sbrk(INIT_MEM);
        sbrk_counter= sbrk_counter +INIT_MEM;
		}

         }



        }

        
		




        buff=ptr_1+size; /*move buff to the end of block*/

        unsigned long addr = (unsigned long) buff;
         
         
         if(addr%16!=0){
         
         
         unsigned long long int small_size=size;
        
        
         if(size<8){
         small_size=size+8;
         }

         unsigned long long int size_result= small_size/8;
         unsigned long long int size_mod =small_size%8;

         if(size_mod!=0){
         	ac_size = 8*(size_result+1);
         }
         else{
         	 ac_size=size_result*8;
         }


        // unsigned long long int ac_size=size+8;

         header=header|a;
         unsigned long long int m_size= size<<32;
         header=header|m_size;
         unsigned long long int b_size =16+ac_size;
         unsigned long long int b_size1=b_size<<3;
         header = header|b_size1;

        
         
         unsigned long long int *assign_header =(unsigned long long int *)ptr_1 ; 
         unsigned long long int *assign_footer =(unsigned long long int *)buff;
         *assign_header = header;
         *assign_footer = header;

          printf("%016llx\n",*assign_header);

        /*assign free block header, footer, next and prev*/
         free_header=buff+8;/*header */
          remain_size= INIT_MEM-b_size;
          unsigned long long int shif_remain=remain_size<<3;
          free_block_info=free_block_info|shif_remain;

          unsigned long long int *assign_freeh =(unsigned long long int *)free_header ; 
          unsigned long long int *assign_freef =(unsigned long long int *)ptr_2 ;
         *assign_freeh = free_block_info;
         *assign_freef = free_block_info;

          size_total=size_total+b_size;
        // void *next = free_header+8;
        // void *prev = free_header+16;

         
         }


        else{

         header=header|a;
         unsigned long long int m_size=size<<32;
         header=header|m_size;
         unsigned long long int b_size =16+size;
         unsigned long long int b_size2=b_size<<3;
         header = header|b_size2;

         unsigned long long int *assign_header =(unsigned long long int *)ptr_1 ; 
         unsigned long long int *assign_footer =(unsigned long long int *)buff ;
         *assign_header = header;
         *assign_footer = header;

          printf("%016llx\n",*assign_header);
        /*assign free block header, footer, next and prev*/
         remain_size= INIT_MEM-b_size;
          unsigned long long int shif_remain=remain_size<<3;
          free_block_info=free_block_info|shif_remain;


          free_header=buff;

          unsigned long long int *assign_freeh =(unsigned long long int *)free_header; 
          unsigned long long int *assign_freef =(unsigned long long int *)ptr_2 ;
         *assign_freeh = free_block_info;
         *assign_freef = free_block_info;
          
          size_total=size_total+b_size;
       //  void *next = free_header+8;
         //void *prev = free_header+16;

        }
      
          
        return ptr_1+8;
       
}



}



/*
* marks a dynamically allocated region as no longer in use
*/
void sf_free(void *ptr){
    
    unsigned long long int current_block_info = *(unsigned long long int*)ptr;
    unsigned long long int current_block_shift;
    unsigned long long int current_block_a;
    

    unsigned long long int prev_block_info;
    unsigned long long int next_block_info;
    unsigned long long int prev_a;
    unsigned long long int next_a;
    unsigned long long int prev_shift;
    unsigned long long int next_shift;
    unsigned long long int prev_final;
    unsigned long long int next_final;

    unsigned long long int new_header;

    
    unsigned long long int final_size; 
    

    void *next;
    void *prev;

    void *next_header;
    void *next_footer;
    void *current_footer;
	void *prev_footer;
    
    //get a of the current block 0x000003
    current_block_a=current_block_info<<63;
    current_block_a=current_block_a>>63;
    
    //get actuall size of the block   0x0000029
    current_block_shift=current_block_info<<32;
    current_block_shift=current_block_shift>>35;

    current_footer=ptr+8+current_block_shift;
    
    //get info of prev block
    prev_footer= ptr-16;
	prev_block_info=*(unsigned long long int*)prev_footer;
	//get a info
	prev_a = prev_block_info<<63;
	prev_a = prev_a>>63;
    //get actuall size info
    prev_shift=prev_block_info<<32;
    prev_final=prev_shift>>35;
	


	//get info of the next block
	next_header=ptr+current_block_shift+8;
	next_block_info=*(unsigned long long int*)next_header;
	//get a info
	next_a=next_block_info<<63;
	next_a=next_a>>63;
	//get actuall size info
	next_shift=next_block_info<<32;
	next_final=next_shift>>35;

	next_footer=next_header+next_final;

	void *old_next=free_header+8;
	void *old_prev=free_header+16;

	current_footer= ptr+current_block_shift;

	if(prev_a ==1){
		//when prev is not empty check next 
		if(next_a==1){

			//when next is also not empty change the current one only and LIFO
			
			new_header=current_block_shift<<3;
			ptr=ptr-8;

            *(unsigned long long int *)ptr =new_header;
            *(unsigned long long int *)current_footer=new_header;

			next = ptr+8;
            prev = ptr+16;
            //LIFO
            next=free_header;
            prev=NULL;
            old_prev=ptr;
            free_header=ptr;

            printf("%p %p %p %p\n",old_prev,old_next,next, prev);
            
            


		}else{
			//when the next one is empty merge the last 2 then LIFO
            final_size = current_block_shift+next_final;
            new_header=final_size<<3;
            ptr=ptr-8;
           *(unsigned long long int *)ptr =new_header;
           *(unsigned long long int *)next_footer=new_header;
            next = ptr+8;
            prev = ptr+16;
            //LIFO
            next=free_header;
            prev=NULL;
            old_prev=ptr;
            free_header=ptr;
             printf("%p %p %p %p\n",old_prev,old_next,next, prev);



		}

	}else{

		//else when prev is empty check next merge
		if(next_a==1){
			//when next is also not empty merge first 2 then LIFO
			final_size=current_block_shift+prev_final;
			new_header=final_size<<3;
			ptr=ptr-16-prev_final;
			*(unsigned long long int *)ptr =new_header;
			*(unsigned long long int *)current_footer=new_header;
			next = ptr+8;
            prev = ptr+16;
			//LIFO
			next=free_header;
            prev=NULL;
            old_prev=ptr;
            free_header=ptr;

             printf("%p %p %p %p\n",old_prev,old_next,next, prev);



		}else{
			//when the next one is empty merge all of them then LIFO
			final_size=current_block_shift+prev_final+next_final;
			new_header=final_size<<3;
			ptr=ptr-16-prev_final;
			*(unsigned long long int *)ptr =new_header;
			*(unsigned long long int *)next_footer=new_header;
			next = ptr+8;
            prev = ptr+16;
			//LIFO
			next=free_header;
            prev=NULL;
            old_prev=ptr;
            free_header=ptr;

             printf("%p %p %p %p\n",old_prev,old_next,next, prev);





		}
	}

    


}



/*
* resizeds the memory pointed to by ptr to be size bytes
*/
void* sf_realloc(void* ptr, size_t size){
printf("realloc");
return NULL;
}


/*
* Allocate an array of nmem elements each of size bytes
*/
void* sf_calloc(size_t nmemb, size_t size){
	
	size_t user_size = nmemb*size;
	void * re_malloc =sf_malloc(user_size);
	if(re_malloc != NULL){
		memset(re_malloc,0,user_size); 	
	}
    //printf("calloc");
	return re_malloc;
}

/*
* funciton which outputs the state of the free-list to stdout
*/
void sf_snapshot(void){
printf("%s %d %lu\n", "Explicit ",8,sbrk_counter);

time_t T = time(NULL);
printf("#%llu\n",(unsigned long long int)T);

void *next_ptr = free_header;
while(next_ptr!=NULL && next_ptr != 0){

    //unsigned long long int size_print = *(unsigned long long int*)next_ptr;
    //size_print=size_print>>3;
	printf("%p %llu\n", next_ptr,(unsigned long long int)(sbrk_counter-size_total));

	next_ptr= (void*)(*(unsigned long long int*)(next_ptr+8));
}
}

/** 
 * THIS FILE SHOULD NOT CONTAIN A MAIN FUNCTION
 * If you want to test these functions make a seperate file
 * and link this one with that file.
 */

