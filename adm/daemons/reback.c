// reback.c ����ȫ��Ψһ�鼮

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define RECALL_HUR 20
#define RECALL_MIN  0
#define PATH     "/clone/lonely/book/"  

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "Ψһ�鼮���վ���");
        write("�鼮���վ����Ѿ�������\n");      
        set_heart_beat(60);
}

private void heart_beat()
{  
     int* lt;     
     lt = localtime(time()); 
    
     if ( lt[3] % 2 == 0 
         && lt[2] == RECALL_HUR && lt[1] == RECALL_MIN) 
     {
        remove_call_out("remind");
        call_out("remind", 1);
     }
     
     
}

void remind()
{
   string msg;   

   msg = HIG"��ϵͳ��Ϣ��ϵͳ��������Ӻ��������Ψһ�鼮����������׼����\n"NOR;  

   message("vision", msg + "\n",users());

        remove_call_out("recall");
        call_out("recall", 300);

}

void recall()
{
     int i;
     object ob, where;
     string *list = get_dir(PATH);

       for(i=0; i<sizeof(list); i++)
       {
             ob = find_object(PATH + list[i]);
             if (! ob) continue;
           //  if (ob) where = environment(ob);          

           //  if ( ! where || ( where && living(where) && ! userp(where) ))
          //       continue;      
             
             message("vision", HIY"ϵͳ������" + ob->name() + "\n"NOR, users());           
             destruct(ob);
       }
       ob = find_object("/clone/book/lbook4");

       if (ob)
       {       
             message("vision", HIY"ϵͳ������" + ob->name() + "\n"NOR, users());           
             destruct(ob);    
       }      
}
