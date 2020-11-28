// recall.c ����ȫ��Ψһ�鼮

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define RECALL_MIN  0
#define PATH     "/clone/lonely/book/"

nosave string *obs = ({
"/clone/book/lbook4",
"/clone/book/pixie_book",
"/clone/book/qiankun_book",
"/clone/book/yijinjing",
"/clone/book/daodejing-i",
"/clone/book/daodejing-ii",
"/clone/book/arrow-book",
});

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "Ψһ�鼮���վ���");
        write("�鼮���վ����Ѿ�������\n");
        remove_call_out("recall");
        call_out("recall", 300);
        set_heart_beat(60);
}

private void heart_beat()
{
     int* lt;
     lt = localtime(time());

     if ( lt[2] % 3 == 0  && lt[1] == RECALL_MIN)
     {
        remove_call_out("recall");
        call_out("recall", 1);
     }


}


void recall()
{
     int i;
     object ob, where;
     string *list = get_dir(PATH);

       for(i=0; i<sizeof(list); i++)
       {
             ob = find_object(PATH + list[i]);
             if (! ob) ob = load_object(PATH + list[i]);
         if ( base_name(ob) == "/clone/lonely/book/dugubook" ||
              base_name(ob) == "/clone/lonely/book/zhenjing" ||
              base_name(ob) == "/clone/lonely/book/zhongping" ||
              base_name(ob) == "/clone/lonely/book/zhaobook" ||
              base_name(ob) == "/clone/lonely/book/yaowang_book" )
              continue;

         ob->set("no_get",1);

         if ( i < 15 )
            ob->move("/d/city/shuyuan3");
         else
         if ( i < 25 )
            ob->move("/d/city/shuyuan4");
         else
         if ( i < 36 )
            ob->move("/d/city/shuyuan5");
         else
         if ( i < 40 )
            ob->move("/d/city/shuyuan6");
         else
         if ( i < 41 )
            ob->move("/d/city/shuyuan7");
         else
            ob->move("/d/city/shuyuan8");
       }

      for(i=0; i<sizeof(obs); i++)
      {
         ob = find_object(obs[i]);
         if (! ob) ob = load_object(obs[i]);
         ob->set("no_get",1);
         ob->move("/d/city/shuyuan7");

     }

     message("vision", HIY"��ϵͳ��Ϣ��Ψһ�鼮�Ѹ��£�"
              "��ҿɵ�������Ժ¥�ϵ���ζ�����Ķ���\n"NOR, users());
}
