#include <ansi.h>
#include <mudlib.h>
#include <getconfig.h>

inherit ROOM; 
int top_list(object ob1,object ob2);
int get_score(object ob);

void create() 
{ 
     set("short", "��  ��"); 
     set("long", @LONG 
�����Ǻ�����������Եĵط���
LONG); 
     set("exits", ([ 
         "east"     : __DIR__"hy_hy01",  
         "down"     : "/d/city/wumiao2" ,
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
}

void init()
{
     add_action("do_xiake","xiake");
}

int do_xiake(object me, string arg)
{
        
        object *list,*ob;
        int i,num;
        string msg;

        ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
        msg =  HIY"\n            ��  "+BRED HIR+LOCAL_MUD_NAME()+"����ʮ������"NOR+ HIY"  ��\n"NOR+HIM;
        msg += "���������ө��ߩ����������������ө����ߩ������ө�����������\n";
        msg += "�� ���� ��    ��        ��    �� ��      �� �� ��    �� ��\n";
        msg += "�ĩ������ة��������������������ة������������ة�����������\n";
        num = 10;

        for (i = 0 ;i < num ; i++) {
                if( i >= sizeof(list)) 
                        msg += "����ʱ��ȱ��                                            �� \n";
                else {
                        if(list[i] != me) msg += BBLU HIY;
                        if(list[i] == me) msg += BYEL HIY;
                        msg += sprintf("��%-7s %-22s%-16s %5d  ��\n"NOR+HIM,
                                       chinese_number(i+1),
                                       list[i]->query("name")+"("+list[i]->query("id")+")",
                                       list[i]->query("family")?  list[i]->query("family/family_name"):"��ͨ����",
                                       get_score(list[i]));
                }
        }
        msg += "����������������������������������������������������������\n";
        msg += HIW"  �����ڵ������ǣ�"+sprintf("%5d",get_score(me))+"��\n"NOR; 
        write(msg);
        return 1;

}
int top_list(object ob1, object ob2)
{
        int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return (score2 >= score1) ? 1 : -1;
}

int get_score(object ob)
{
        int score;
        score = ob->query("shen");
        return score;
}

