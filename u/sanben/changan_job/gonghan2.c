//�������񹫺�2
//��ϳ���������ɱҰ������ĵ���

#include <ansi.h>
inherit ITEM;



void create()
{
        set_name(NOR + HIY "����������" NOR, ({ "gong han", "gonghan", "han" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�ݳ��������ŵĹ�����������(read gong han)���Ķ���\n");
                set("value", 0);                
        }
        setup();
}

void init()
{
     add_action("do_read","read");     
}

int do_read( string arg )
{
    string msg, space;
    int i;
    msg = "";
    space = "                                            ";
    
    if ( !arg || ( arg != "gong han" && arg != "gonghan" && arg != "han") )
    return notify_fail("��Ҫ��ʲô��\n");

    msg = HIY"                      ����������\n\n"NOR;
    msg += WHT"    ���ճ�������ʱ�����޳�û���˼����ա�����ǲ�����ʿ\n"NOR;
    msg += "                        "HIC + query("owner") + NOR WHT
           "\n    Э���ٸ���ɱ���ޣ��Ա�̫ƽ��\n";
    msg += "    �ݳƣ�ʱ�±���  "WHT;

    for( i=0; i < strlen(query("place"))/2; i++ ) 
    { msg += "\n                  " // + space[0..random(10)]
          + query("place")[(i*2)..(i*2+1)]; } 

    msg += "\n    ��Ұ�޳�û�ڶ࣬�ɾ�ȥ�˴����(ambush)�ȴ�������ɱ��\n";
    msg += HIR"                   ��ȥ�ٻأ���������\n";   
    msg += "                   ����֪��������» ǩ��"NOR;
    write( msg  +"\n");
    return 1;
}