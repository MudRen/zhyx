//�������񹫺�1
//��ϳ���������Ѳ�ǵĵ���

#include <ansi.h>
inherit ITEM;



void create()
{
        set_name(NOR + HIG "����������" NOR, ({ "gong han", "gonghan", "han" }));
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
    int i, ii;
    msg = "";   
    
    if ( !arg || ( arg != "gong han" && arg != "gonghan" && arg != "han") )
    return notify_fail("��Ҫ��ʲô��\n");

    msg = HIG"                      ����������\n\n"NOR;
    msg += HIY"    ���ճ�������ʱ�е�����û�����Ӱ��ա�����ǲ�����ʿ\n"NOR;
    msg += "                        "HIC + query("owner") + NOR HIY
           "\n    Э���ٸ�Ѳ��׽�����Ա�̫ƽ��\n";
    msg += "    ��Ѳ�Ӹ����ص�����:  \n"HIY;
    for( i=0; i < 6; i++ ) 
    {       
       for( ii=0; ii < 5; ii++ ) 
       { if (ii == 0) msg += "               ";
         if ( query("place/"+(ii+1))[(i*2)..(i*2+1)] != "") 
         msg += query("place/"+(ii+1))[(i*2)..(i*2+1)] + "    "; 
         else
         msg += "      "; 
       }     
         msg += "\n";   
    }
    for( ii=0; ii < 5; ii++ ) 
       { if (ii == 0) msg += "               ";
         if ( query("placeok/"+(ii+1)) ) 
         msg += HIG"��"NOR+ "    "; 
         else
         msg += HIW"δ"NOR + "    "; 
       } 
    msg += "\n";
    for( ii=0; ii < 5; ii++ ) 
       { if (ii == 0) msg += "               ";
         msg += HIC"Ѳ"NOR + "    "; 
       } 
    msg += "\n";
    msg += NOR HIR"                   ��ȥ�ٻأ���������\n";
    msg += "                  ����֪��������» ǩ��\n"NOR;
    write( msg  +"\n");  
    return 1;
}