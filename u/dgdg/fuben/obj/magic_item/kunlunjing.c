// �Ϲ�ʮ������֮ ���ؾ�
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

// �ɴ���ĵص�
mapping place = ([
        "beijing"   : "/d/beijing/majiu",
        "yangzhou"  : "/d/city/majiu",
        "dali"      : "/d/dali/majiu",
        "foshan"    : "/d/foshan/majiu",
        "fuzhou"    : "/d/fuzhou/majiu",
        "guanwai"   : "/d/guanwai/majiu",
        "hangzhou"  : "/d/hangzhou/majiu",
        "lanzhou"   : "/d/lanzhou/majiu",
        "lingzhou"  : "/d/lingzhou/majiu",
        "luoyang"   : "/d/luoyang/majiu",
        "yongdeng"  : "/d/huanghe/majiu",
        "suzhou"    : "/d/suzhou/majiu",
        "xiangyang" : "/d/xiangyang/majiu",
        "yili"      : "/d/xingxiu/majiu",
        "chengdu"   : "/d/city3/majiu",
        "emei"      : "/d/emei/majiu1",
        "emei2"     : "/d/emei/majiu2",
        "quanzhou"  : "/d/quanzhou/majiu1",
        "jiaxing"   : "/d/quanzhou/majiu2",
        "jingzhou"  : "/d/jingzhou/majiu",
        "nanyang"   : "/d/shaolin/majiu1",
        "changan"   : "/d/changan/majiu",
        "wugong"    : "/d/quanzhen/majiu",
        "hengyang"  : "/d/henshan/majiu",
        "kaifeng"   : "/d/kaifeng/majiu",
        "kunming"   : "/d/kunming/majiu",
        "zhongzhou" : "/d/zhongzhou/majiu",

]);

void create()
{
        set_name(HIW "���ؾ�" NOR, ({ "kunlun jing", "kunlun", "jing" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "��");
                set("long", HIW "����һ��ͨ������ľ��ӣ���˵ӵ�д���ʱ�յ�������\n"                               
                                "�ɽ����䴩��(trans)�����������ǣ��������� trans �鿴\n"
                                "�ɴ���ĵص㣬ʹ�� trans ? �鿴ʹ�ô�����\n" NOR);                

        }

        setup();
}

void init()
{
        add_action("do_trans", "trans");
}

int do_trans(string arg)
{
        object me;
        string *places;
        int i;
        
        me = this_player();
        
        if(! objectp(present("kunlun jing", me)))return 0;
                
        places = keys(place);
        if (! arg)
        {
              write(HIC "����Դ������µص㣺\n");
              for (i = 0; i < sizeof(places); i ++)
                      write(places[i] + "\n");
              
              return 1;
        }
        if (arg == "?")
        {
        	 write(HIG "ʹ�ô��� " + this_object()->query("count") + "/30\n" NOR);
        	 return 1;
        }
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("����æ�أ�\n");
                         
        if (member_array(arg, places) == -1)
                 return notify_fail("�������û����Ҫ���ĵط���\n");                

        message_sort(HIW "\n$N" HIW "���������е����ؾ���ɲ�Ǽ�⻪�����$N" HIW "��"
                         "�������â��ʧ����� ����\n" NOR, me);

        write(HIG "�������£������˵��ϡ�\n" NOR);
        
        me->move(place[arg]);        
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 30)
        {
        	write(HIW "ֻ����һ�����������������ؾ��Ѿ����ˣ�\n" NOR);
        	destruct(this_object());        	        	
        }
        
        return 1;
}
