inherit ITEM;

mapping places=([
"bt" : "/d/baituo/dating.c",
"tam": "/d/beijing/tiananmen",
"gc" : "/d/city/guangchang.c",
"lj" : "/d/lingjiu/damen.c",
"sl" : "/d/shaolin/guangchang1.c",
"wd" : "/d/wudang/sanqingdian.c",
"xy" : "/d/xiaoyao/qingcaop.c",
"xx" : "/d/xingxiu/xxh2.c",
"hs" : "/d/huashan/square.c",
"yzw" : "/d/yanziwu/bozhou.c",
"xs" : "/d/xueshan/dadian.c",
//"kl" : "/d/gaochang/room63.c",
//"ny" : "/d/nanyang/nanyang.c",
"qz" : "/d/quanzhou/zhongxin.c",
"cd" : "/d/city3/guangchang.c",
"ca" : "/d/changan/baihu2",
"dl" : "/d/dali/center",
//"wdj": "/d/wudujiao/dating.c",
"em" : "/d/emei/caopeng",
"mj" : "/d/mingjiao/mjsimen1",
]);

void create()
{
       set_name("ħ��������", ({ "trans site","site"}) );
    set_weight(500);
    if (clonep())
        set_default_object(__FILE__);
    else {
            set("long",
        "\n����һ��ħ���������������ķ������Ե���(trans)�ĵط���\n\n"
        "   gc : ���ݹ㳡     tam : �찲��     bt : ����ɽ\n"
        "   lj : ���չ�       sl  : ������     wd : �䵱ɽ\n"
        "   xy : ��ң��       xx  : ���޺�     xs : ѩɽ��\n"
        "   hs : ��ɽ         cd  : �ɶ�       qz : Ȫ��  \n"
        "   dl : ����         ca  : ����       em : ��ü  \n"
        "   mj : ����           yzw : ������                   \n\n"

"set msg_min <anything>        �趨��ʹ��ħ������������ĳ��ʱ, ������������ѶϢ��\n"
"set msg_mout <anything>       �趨��ʹ��ħ���������뿪ʱ, ԭ�������������������ѶϢ��\n\n"

        );
            set("unit", "��");
            set("value", 1000);
    }
    setup();
}
void init()
{
    if ( !this_player()->is_ghost() )
    add_action("do_trans","trans");
}
int do_trans(string arg)
{
        object me,room,ob,*obj;
    string msg;
        int i;
    me=this_player();

    if( ! environment()->is_character() ) return 0;
    if (me->query("age")>17)     return notify_fail("������ֻ�ʺ�С����ʹ�á�\n");
    if( !arg ) return notify_fail("��Ҫȥ���\n");
    if (me->is_fighting())
         return notify_fail("ս�����޷�ʹ��ħ�����ͣ�\n");
    if  (!environment(me)->query("outdoors"))
         return notify_fail("�ڷ��������޷�ʹ��ħ�����ͣ�\n");
    if (!stringp(places[arg]))  return notify_fail("��Ҫȥ���\n");
    if (present("biao yin",me)) return notify_fail("�����ϴ����������޷�ʹ��ħ�����ͣ�\n");

     obj=deep_inventory(me);
     for (i=0;i<sizeof(obj);i++)
           if (obj[i]->id("illicit salt"))
         return notify_fail("�����ϴ���˽�Σ��޷�ʹ��ħ�����ͣ�\n");

    ob=first_inventory(me);
    while(ob){
        if (ob->is_character() && !ob->is_corpse() )
            return notify_fail(ob->name()+"���ܺ���һ��Խʱ��֮�ţ�\n");
        ob=next_inventory(ob);
    }
    if (me->query("jing") < 10) return notify_fail("�㾫������������ʹ��ħ�����ͣ�\n");
    if( stringp(msg = me->query("env/msg_mout")) )
       {if (msg!="") message_vision(msg+"\n", me);}
    else
        message_vision("ֻ��һ��������ᣬ$N����Ӱ�Ѿ������ˡ�\n", me);
    if (!room=find_object(places[arg]) )
        room=load_object(places[arg]);
    me->move(room);
    if( stringp(msg = me->query("env/msg_min")) )
       {if (msg!="") message_vision(msg+"\n", me);}
    else
        message_vision("$N����ӰͻȻ������һ������֮�С�\n", me);
    me->receive_damage("jing", 10);
    return 1;
}
void owner_is_killed() { destruct(this_object()); }

