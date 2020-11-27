#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>

string *garbage =
({
        "/clone/weapon/changjian",
        "/clone/cloth/junfu",
        "/clone/horse/mapi",
        "/clone/weapon/blade",
        "/clone/weapon/gangdao",
        "/d/room/obj/paper",
});

int clean_up() { return 1; }

void auto_relaim();

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "ϵͳ����");
        CHANNEL_D->do_channel( this_object(), "sys", "ϵͳ�������Ѿ�������");
  
        call_out("auto_clear",10);
}

void auto_clear()
{
        object *list,where;
        int i,j,num;

        remove_call_out("auto_clear");
        call_out("auto_clear", 900);

        for (i = 0;i < sizeof(garbage);i ++)
        {
                num = 0;
                if (file_size(garbage[i] + ".c") < 0) continue;
                list = children(garbage[i]);
                if (!sizeof(list)) continue;
                for (j = 0;j < sizeof(list);j++)
                {
                        where = environment(list[j]);
                    if (!where || where->query("short"))
                        {
                                destruct(list[j]);
                                num ++;
                        }
                }
                if (num)
                        CHANNEL_D->do_channel( this_object(), "sys",
                               sprintf("ϵͳ�Զ���� %d " + garbage[i]->query("unit") + 
                               garbage[i]->name(1) + "��", num));
        }
       //���ַ����������������ͷ
       where = find_object("/d/shaolin/fzlou2");
       if (!where) return;
       list = all_inventory(where);
       for (i = 0;i < sizeof(list);i ++)
       {
           if (base_name(list[i]) == "/clone/misc/head")
              destruct(list[i]);
       }

       //Ļ�ݼ����������ͷ
       where = find_object("/d/yanziwu/canheju");
       if (!where) return;
       list = all_inventory(where);
       for (i = 0;i < sizeof(list);i ++)
       {
           if (base_name(list[i]) == "/clone/misc/head")
              destruct(list[i]);
       }
      
}
