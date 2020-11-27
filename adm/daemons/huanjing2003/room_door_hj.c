//                ��׼��������ʾ��                                   |
// �����þ�֮�������� ֮�����
// ������Ʊ����Ʊ����ع����ڴ˽��У�������������ң�������ת������һ��ͨ�������ڡ�
// by naihe  2002-11-03  ��ï��

// �Ѿ��ı�������������ˡ���
// naihe 17:07 03-11-1 

#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include <ctime_format_func.h>

// ���ļ�������Ϸ��ͼ��С
#include "npc_obj/hj_settings/room_amount_hj.h"
// ���ļ�������Ϸ�汾��  HJ2003_VERSION
#include "npc_obj/hj_settings/game_version.h"

// ##################################
// ##########  һЩ�궨�� ###########
// ##################################
#define        HJ_DOOR_DATA    "/data/huanjing/door_data"
// �������ϵ��ļ���
#define        HJ_ROOM_CREATE_D    "/adm/daemons/hj_room_created"
// ���ļ�ӵ���㹻Ȩ�޽���д�ļ��Ĳ�����

#ifndef        HJ_DIR
#define        HJ_DIR        __DIR__
#endif


////////////////////////////////////////////////////
//// ������ֵ����ָ�� (mewiz) ���ģ����Զ����� /////
////////////////////////////////////////////////////

int GAME_OPEN = 1;
// ����Ϸ�Ƿ񿪷š� 1���ţ�0�ر�
// �ر�ʱ���κ��˲��ý��루��ʦ������Ҳ�޷���Ϸ��
// ������ mewiz ָ�����ֵ�����������಻��ָ���

int FREE_GAME = 0;
// �����Ϸ�� 1 ���ţ�0�ر�
// �����ñ����� GAME_OPEN Ϊ����״̬ʱ����Ч��
// ˵��ͬ��

int MAX_HJ_ENTER = 10;
// ���������������������ʱ����Ҳ��ü���������Ϸ��

int MP_GOLD = 20;
// ��Ʊ�۸񣨻ƽ𣩣�ʹ��Ǯׯת��

int MSG_GOLD = 5;
// ��Ϣ�۸�ʹ��Ǯׯת��

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

// ##################################
// ##########  ����ͳ��  ############
// ##################################

// �����˴Σ��������
int in_times, max_in_hj, in_money, buy_piao_times, buy_sm_times, buy_msg_times;

mapping player_level_info = ([ ]);

// ##################################
// ##################################


string look_ban();
string look_pai();
string del_player_level( string id );
void lucky( object me );

string query_save_file()
{
    return HJ_DOOR_DATA;
}

// �������ʹ�������¼�����ݲ�����������ڷǱ���������NPC����Ʒ�����벻�����£�����Ҫ���������� no_refresh ���
void reset()
{
    ::reset();
    set("no_clean_up", 1);
}

// ��������������ɫ�ص���
void hjset_short()
{
    string *color, cl1, cl2, cl3, cl4, cl5, cl6, cl7;
    int size;

    color = ({ HIY, HIR, HIB, HIG, HIC, HIW, HIM });

    // ���ȥ��4����ɫ����ô7������ͬ��ɫ�ĸ��ʾʹ��˺ܶ�ܶ�
    if( !random(5) )
    {
        size = 4;
        while( size-- ) color -= ({ color[ random( sizeof(color) ) ] });
    }

    size = sizeof( color );
    cl1 = color[ random(size) ];
    cl2 = color[ random(size) ];
    cl3 = color[ random(size) ];
    cl4 = color[ random(size) ];
    cl5 = color[ random(size) ];
    cl6 = color[ random(size) ];
    cl7 = color[ random(size) ];

    set("color_short_hj",cl1+"ң"+cl2+"Զ"+cl3+"��"+cl4+"˵"+cl5+"֮"+cl6+"��"+cl7+"Ե"NOR);
    set("short", MAG"�þ�2003 "+HJ2003_VERSION+NOR );

    if( cl1 == cl2 && cl1 == cl3 && cl1 == cl4 && cl1 == cl5 && cl1 == cl6 && cl1 == cl7 )
        set("same_color", 1);
    else set("same_color", 0);
}

mapping who_in_hj()
{
    object rooms, *in_env;
    int i,j,amount;
    string msg, *all_ip=({});

    msg = "";
    // ������������������ص�
    rooms = find_object( __DIR__"room_master_hj");
    if( rooms )
    {
        in_env = all_inventory( rooms );
        if( in_env && sizeof(in_env) )
        {
            for( j=0;j<sizeof(in_env);j++ )
            {
                if( userp(in_env[j]) )
                {
                    amount++;
                    msg += sprintf( "%s\n",
                        in_env[j]->short());
                    all_ip += ({ query_ip_name( in_env[j] ) });
                }
            }
        }
    }

    rooms = find_object( __DIR__"room_readygo_hj");
    if( rooms )
    {
        in_env = all_inventory( rooms );
        if( in_env && sizeof(in_env) )
        {
            for( j=0;j<sizeof(in_env);j++ )
            {
                if( userp(in_env[j]) )
                {
                    amount++;
                    msg += sprintf( "%s\n",
                        in_env[j]->short());
                    all_ip += ({ query_ip_name( in_env[j] ) });
                }
            }
        }
    }

    // ���������
    for( i=1;i<=HJ_ROOM_AMOUNT;i++ )
    {
        rooms = find_object( __DIR__"hj_room"+i );
        if( !rooms ) continue;
        in_env = all_inventory( rooms );
        if( !in_env || !sizeof(in_env) ) continue;
        for( j=0;j<sizeof(in_env);j++ )
        {
            if( userp(in_env[j]) )
            {
                amount++;
                msg += sprintf( "%s\n",
                    in_env[j]->short());
                all_ip += ({ query_ip_name( in_env[j] ) });
            }
        }
    }

    if( !amount ) msg = "�þ�������û���κ���ҡ�\n";
    else  msg = "��������������Լ��þ������ڣ����ڹ���"+chinese_number( amount )+"λ��ң�\n" + msg;

    if( amount > max_in_hj )
    {
        max_in_hj = amount;
        save();
    }

    set( "all_ip_in_hj", all_ip );
    return ([ "amount": amount, "info": msg ]);
}


// �κΰ����ſڵ�Ч��д��2��Сʱ�������������ļ������֣���С�ط�
//         ����8�Σ��١�
void hjset_long()
{
    mapping temp;
    string temp_str, longs;

    if( !GAME_OPEN ) temp_str = HIR"     (��Ϸ�ر�)"NOR;
    else if( FREE_GAME )
        temp_str = sprintf( HIC"(��ѿ��š�����%2d��)"NOR,
                who_in_hj()["amount"] );
    else temp_str = sprintf( HIG"(�������š�����%2d��)"NOR,
                who_in_hj()["amount"] );

    longs= "\n        �� "HIW"�q���������������������������������������������r     
           "NOR+WHT"�t�r   "NOR+WHT"�þ� �� "+query("color_short_hj")+NOR+WHT" �� ��������"NOR+WHT"   �q�s     
           "NOR+HIW"�q�s            "NOR+WHT"BY naihe 2003.10"NOR+HIW"            �t�r     
           "NOR+WHT"�t���������������������������������������������s     "NOR"
                         "+temp_str+"

    ��̤����һ���İ������ڣ�����������Լ������ȴ���޷�����Դͷ��һ��
  �޴��ľ��(ban)Ʈ����������ǰ��Զ֮�����֣��ް��´���һ��Сľ��(pai)��
������Ǵ�˵�еġ��þ�������ʵ֮��Ľӿڣ��ɴ˶������㽫��֮���������ص�
                          �þ�֮�أ��������ڡ���

    ----------------------------------------------------------------\n";

    // ��ʽ
    //    set("player_msg3", ([ "id": "12345678", "time":"03.10.24", "msg":"����" ]) );
    if( query("player_msg1") )
    {
        temp = query("player_msg1");
        longs += sprintf("    �� %-8s ������Ϣ(%8s):%-32s��\n", 
            temp[ "id" ], temp[ "time" ], temp["msg"] );
    }
    if( query("player_msg2") )
    {
        temp = query("player_msg2");
        longs += sprintf("    �� %-8s ������Ϣ(%8s):%-32s��\n", 
            temp[ "id" ], temp[ "time" ], temp[ "msg" ] );
    }
    if( query("player_msg3") )
    {
        temp = query("player_msg3");
        longs += sprintf("    �� %-8s ������Ϣ(%8s):%-32s��\n", 
            temp[ "id" ], temp[ "time" ], temp[ "msg" ] );
    }

    if( !query("player_msg1") && !query("player_msg2") && !query("player_msg3") )
        longs += sprintf("             �� %s ��\n", "����û����ҷ�����Ϣ (ָ�hjmsg ����)");

    set( "long", longs + 
"    ----------------------------------------------------------------\n" );
}

void create()
{
    restore();
    // ������ʷͳ��
    if( !query("begin_time") )
        set("begin_time", time() );

    hjset_short();
    hjset_long();

    // ���Ǹ����ڹ�������Ϣ
    if( random(3) )
        set("player_msg1", ([ "id": "naihe", "time":"03.10.24",
            "msg":"������壺����С��(12)��С��(10)" ]) );

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("valid_startroom", 1);

    set("item_desc",([
        "ban": (: look_ban :),
        "pai": (: look_pai :),
    ]));

    set("exits", ([
        "down":"/d/city/guangchang",  // ��������㳡ʹ�� jump ָ����롣
        "enter":__DIR__"room_master_hj",
        "up":__DIR__"room_cession_hj",
        ]));

// ���� cs ���룺
/*
void init()
{
    add_action("do_enter_hj", "jump");
}

int do_enter_hj(string arg)
{
    object rooms, me=this_player();
    if( !arg || arg != "up" ) return 0;

    rooms = find_object( "/adm/daemons/huanjing2003/room_door_hj" );
    if( !rooms ) rooms = load_object( "/adm/daemons/huanjing2003/room_door_hj" );
    if( !rooms ) return 0;

    tell_room( environment(me), me->query("name")+"ʹ��������һ����ͻȻ����һ�����磬"+me->query("name")+"��ʱ����εò�֪���١�\n", me);
    me->move(rooms);
    write("��ʹ��������һ��������ƽ�ؾ���һ�����磬��������������ˡ��þ�����\n");
    tell_room( rooms, "��Ȼһ������Ϯ����"+me->query("name")+"�ѳ��������\n", me );
    return 1;
}
*/

    setup();
}

void init()
{
    object me = this_player();
    
    if( !userp(me) || !living(me) )
        return;
    me->delete_temp( "hj2003-valid_enter" );
    if( me->query_temp( "hj_apply_short" ) )
    {
        me->delete_temp( "hj_apply_short" );
        me->delete_temp( "apply/short" );
    }
    if( wizardp(me) )
    {
        add_action("do_mewiz","mewiz");
        add_action("do_create_room_file", "create_room_file");
    }
    add_action("do_maipiao","maipiao");
    add_action("do_goumai","goumai");
    add_action("do_msg", "hjmsg");
    add_action("do_top", "top");
    add_action("do_huanjing", "huanjing");
    add_action("do_who_in_hj", "gwho");
    add_action("do_look", "look");

    if( !me->query("huanjing2003")
      || !mapp(me->query("huanjing2003"))
    )
    {
        me->delete("huanjing2003");
        me->set("huanjing2003/welcome_to_hj_time", ctime_format() );
    }

    // ��������ɾ����ǰ�İ汾ʱ���������ӵ���Ϣ�ġ�
    me->delete("aaaaa_hj_award");
    me->delete("aaaaa_hj_gift");

    // ɾ���Ƿ��� level ��
    if( me->query("huanjing2003/lv") && undefinedp( player_level_info[getuid(me)] ) )
    {
        me->delete("huanjing2003/lv");
        me->save();
        call_out( "xxxxx", 1, me );
    }
    hjset_short();
    hjset_long();
    if( query("same_color") )
    {
        me->start_busy(5);
        lucky( me );
    }
}

void xxxxx( object me )
{
    if( !me ) return;
    message_vision( "$Nֻ�������巢����һЩ�仯��$N�ġ��þ����ȼ���ɾ���ˡ�������ϵ�þ���ʦ��\n", me);
}


void lucky( object me )
{
    if(!me || !environment(me) || environment(me) != this_object() ) return;

    message_vision("
$N���߹�����ͻȻһ��䶯֮��������ֻ���Ա߳����������ģ�������ˣ�
����һ����ò�Źֵ�Ů��˵����$N˵��������ϲ��ϲ���þ����ڷ����ر�����������ε������ߣ���
����һ���Ƚ��������˵����ӽ���˵����������Ҫ����þ��Ļ���������ر�Ľ�������
ֻ������һ���ƵĶ�����$N����΢΢һ�𣬾���ʲô����������ײ��һ��һ�㣡
�⼸���˺�����ȥ��˵���侹Ȼ�ʹ����£��������ȥ�ˡ�\n\n",me);
    me->set("huanjing2003/gift","����");
    me->save();
}

int do_look(string arg)
{
    if( !arg ) hjset_long();
    return 0;
}

string look_pai()
{
    return "#################################################################################
����Ϸ��Ҫ��Ʊ���룬������Ϸ��ѿ��š��۸� "+HIR+MP_GOLD+NOR" GOLD��ָ�"HIY"(maipiao)"NOR"
���귢����Ϸ˵���ֲᣬ�۸� "HIR"1"NOR" GOLD��ָ� "HIY"(goumai shuoming)"NOR"
��ҿ��Է�����Ϣ���۸� "+HIR+MSG_GOLD+NOR" GOLD��ָ�"HIY"(hjmsg)"NOR"
��ҿ��Բ�ѯ˭�ڻþ���Ϸ�ָ�"HIY"(gwho)"NOR"
�þ���Ϸ��ع��漰��Ѷ��ָ�"HIY"(huanjing list)"NOR"
#################################################################################\n";
}

int do_who_in_hj()
{
    write( who_in_hj()[ "info" ] );
    return 1;
}

int do_huanjing( string arg )
{
    string *dirs, msg;
    int i;

    if( !arg ) return notify_fail("���ָ���������鿴�þ���Ϸ��һЩ�����������Ϣ��\n������ (huanjing list) ָ��鿴�б�\n");

    if( arg == "list" )
    {
        dirs = get_dir( __DIR__"other_info/" );
        if( !dirs || sizeof( dirs ) < 1 )
            return notify_fail("����û���κμ�¼��\n");
        msg = "============= �����ǻþ���Ϸ�Ĺ��漰��Ϣ��¼��=============\n\n";

        for( i=0; i<sizeof( dirs ); i++ )
        {
            msg += sprintf( "���þ���Ϸ���¼��  --  %s\n",
                replace_string( dirs[i], ".naihe", "" ) );
        }

        msg += "\n========== ����ָ�� (huanjing ��¼��) �鿴���� ===========\n";
        this_player()->start_more( msg );
        return 1;
    }

    if( file_size( __DIR__"other_info/"+ arg +".naihe" ) < 1 )
        return notify_fail("�޸ü�¼��ü�¼�����ݡ�\n");

    msg = read_file( __DIR__"other_info/"+ arg + ".naihe" );
    if( !msg ) return notify_fail("�޷���ȡ�ü�¼���ݡ�\n");

    msg = "============== "+arg+ " ����ȫ�� ==============\n\n"+ msg + "\n\n===================================================\n";
    this_player()->start_more( msg );
    return 1;
}


int do_goumai(string arg)
{
    object me=this_player(),gold;

    // ��ɾ�������
    return notify_fail("��ֱ������ help hj2003 ��ѯ��Ϸ˵����\n");

    if(!arg || arg!="shuoming")
        return notify_fail("������Ϸ˵���ֲᣬ�۸�1 GOLD��ָ�� <goumai shuoming> ��\n");

    gold = present("gold_money",me);
    if(!gold) return notify_fail("������û�лƽ�\n");
    gold->add_amount(-1);
    new(__DIR__"other_obj/obj_shows")->move(me);
    message_vision("$N�ͳ�һ���ƽ�������һ����Ϸ˵���ֲᡣ\n",me);
    in_money ++;
    buy_sm_times ++;
    save();
    return 1;
}

string look_ban()
{
    object out_room;

    write("
       ������������������������������������
       �� "WHT"�þ���"+query("color_short_hj")+NOR+WHT"����������"NOR" ��
       ������������������������������������
");

    out_room = find_object( __DIR__"room_gameover_hj" );
    if( !out_room ) out_room = load_object( __DIR__"room_gameover_hj" );
    if( out_room ) write( out_room->get_TOP_pic()+"\n"NOR);

    if(wizardp(this_player()))
        write("\n������ʦ����ʹ�� <mewiz> ָ��������ѯ <mewiz> ��");

    return "\n";
}

int do_top(string arg)
{
    if( !arg || (arg != "hj" && arg != "huanjing") )
        return 0;

    write("��ľ������д����߳ɼ���¼�ء�\n");
    return 1;
}

int do_msg( string arg )
{
    object me = this_player();
    string time;

    if( !arg ) return notify_fail("<hjmsg> ָ����������ڻþ���ڴ�������Ϣ��
ÿ�η�����Ϣ��Ҫ "HIR+MSG_GOLD+" ���ƽ� "NOR"����Ǯׯ�Զ�ת�ʡ�
��ֻ�ܷ������Ȳ�����16�����ֵ���Ϣ��
�㷢������Ϣ���ܻᱻϵͳ���κ�ʱ���������߱��������·�������Ϣ������
ָ���ʽ�� msg ����\n");

    if( strlen( arg ) > 32 )
        return notify_fail("��ֻ�ܷ����������Ϊ16�����ֵ���Ϣ��\n");

    if( arg == "clean" && wizardp(me) )
    {
        message_vision("$N�����ڷ�������Ϣ������ˡ�\n",me);
        delete("player_msg1");
        delete("player_msg2");
        delete("player_msg3");
        hjset_long();
        save();
        return 1;
    }

    if( me->query("balance") < MSG_GOLD * 10000 )
        return notify_fail("���Ǯׯ�������޷�������Ϣ��\n");

    // OK,����

    me->add("balance", - MSG_GOLD*10000 );

    if( query("player_msg2") )
        set( "player_msg1", query("player_msg2") );
    if( query("player_msg3") )
        set( "player_msg2", query("player_msg3") );

    time = ctime_format( "Y.M.D" );
    set( "player_msg3", ([ "id": me->query("id") , "time": time, "msg": arg ]) );
    hjset_long();
    message_vision("$N֧����"+chinese_number(MSG_GOLD)+"���ƽ𣬷�����һ�����Ϣ��\n",me);

    in_money += MSG_GOLD;
    buy_msg_times ++;

    save();
    return 1;
}

int do_mewiz(string arg)
{
    int temp, time, i;
    object ts;
    string msg, *key;
    mixed ppp;

    if(!wizardp(this_player())) return 0;

    if(!arg) return notify_fail(
"�ɲ�����������(���� <mewiz open 1>��
open 1          --> ��Ϸ����
open 0          --> ��Ϸ�ر�
free 1          --> ���������Ϸ
free 0          --> �ر������Ϸ
mpgold ����     --> ��Ʊ�۸�(�ƽ�)
msggold ����    --> ������Ϣ�۸�(�ƽ�)
maxenter ����   --> ������������������ҵ��������ʱ�����ٷ��˽���
ts              --> ��ȡ��ʦר�õ� �þ�����
ck              --> ��ѯ��ǰ��Ϸ����������״̬
cklevel         --> ��ѯ���лþ���ҵ� level ״̬
dellv ID        --> ���ĳ���������� level ��¼(���������ʵ����Ч level)\n");

    if( arg == "ts" )
    {
        ts = new( __DIR__"npc_obj/hj_wiztools" );
        ts->move(this_player());
        write("OK����ȡ��һ�� �þ���ʦ���ߡ�\n");
        return 1;
    }

    if( arg == "cklevel" )
    {
        if( !player_level_info || !sizeof(player_level_info) )
            return notify_fail("���ڻ�û���κ���ҵ� level ��¼��\n");

        key = keys( player_level_info );
        msg = "���� "+sizeof(key)+" ����¼����ϸ�������£�\n\n";
        for( i=0;i<sizeof(key);i++ )
        {
            ppp = player_level_info[ key[i] ];
            if( !mapp(ppp) ) continue;
            time ++;
            msg += sprintf( "%s(%s)  LV %d    (%s)\n",
                ppp["name"], key[i], ppp["lv"], ctime_format( ppp["time"] ) );
        }
        msg += "\n��Ч��¼�� "+time+" ����\n";
        this_player()->start_more( msg );
        return 1;
    }

    if( sscanf( arg, "dellv %s", msg ) )
    {
        if( getuid( this_player() ) != "naihe" )
            return notify_fail("��ָ��ֻ�����κ�ִ�С�\n");
        write( del_player_level( msg ) );
        return 1;
    }

    if(arg == "ck")
    {
        time = query("begin_time");
        temp = time() - time;

        msg = sprintf("
************************************************************
%s         ����볡�������ƣ�%d
%s
ϵͳ�����ڣ�%s ��
�����ǣ�    %s ��

    "HIY"�����ѹ��� %d �� %d Сʱ %d ���� %d ��"NOR"

���볡�˴�(������ʦ)��"HIG"%-10d"NOR" ���ͬʱ�ڳ���"HIC"%d"NOR"
    (ƽ��ÿ %d �� %d Сʱ %d �� %d �����һ�˴�)
�����룺"HIY"%d"NOR" �ƽ� (��Ʊ %d �ţ�������Ϣ %d �Σ��۳�˵�� %d ��)
(��Ʊ %d GOLD / �ţ�˵�� 1 GOLD / ����������Ϣ %d GOLD / ��)
************************************************************\n",
            GAME_OPEN ? HIG"����Ϸ  -->������"NOR : HIR"����Ϸ  -->�ر���"NOR,
            MAX_HJ_ENTER,
            FREE_GAME ? HIY"�����������Ϸ��"NOR : HIG"������������Ϸ������ѡ�"NOR, 
            ctime_format( time ), ctime_format(), 
            temp / 86400, (temp % 86400) / 3600,
            (temp % 86400 % 3600) / 60, temp % 86400 % 3600 % 60,
            in_times, max_in_hj,
            in_times ? (temp / in_times) / 86400 : 0,
            in_times ? ((temp / in_times) % 86400) / 3600 : 0,
            in_times ? ((temp / in_times) % 86400 % 3600) / 60 : 0,
            in_times ? ((temp / in_times) % 86400 % 3600) % 60 : 0,
            in_money, buy_piao_times, buy_msg_times, buy_sm_times,
            MP_GOLD, MSG_GOLD );
        write( msg );
        return 1;
    }

    if( sscanf(arg, "open %d", temp) )
    {
        if(temp!= 1 && temp!=0) return notify_fail("ֻ������ 1 �� 0 ������/�ر���Ϸ��\n");

        GAME_OPEN = temp;
        write("���óɹ������� <mewiz ck> ָ���ѯ��ǰ״̬��\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf(arg, "free %d", temp) )
    {
        if(temp!= 1 && temp!=0) return notify_fail("ֻ������ 1 �� 0 ������/�ر������Ϸ��\n");

        FREE_GAME = temp;
        write("���óɹ������� <mewiz ck> ָ���ѯ��ǰ״̬��\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf( arg, "mpgold %d", temp ) )
    {
        if( temp< 1 || temp > 1000 ) return notify_fail("������Ʊ�۸񣬷�Χ 1-1000 �ƽ�\n");

        MP_GOLD = temp;
        write("���óɹ������� <mewiz ck> ָ���ѯ��ǰ״̬��\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf( arg, "msggold %d", temp ) )
    {
        if( temp< 1 || temp > 1000 ) return notify_fail("���÷�����Ϣ�۸񣬷�Χ 1-1000 �ƽ�\n");

        MSG_GOLD = temp;
        write("���óɹ������� <mewiz ck> ָ���ѯ��ǰ״̬��\n");
        hjset_long();
        save();
        return 1;
    }

    if( sscanf( arg, "maxenter %d", temp ) )
    {
        if( temp< 1 || temp > 100 ) return notify_fail("������������������Χ 1-100 ��\n");

        MAX_HJ_ENTER = temp;
        write("���óɹ������� <mewiz ck> ָ���ѯ��ǰ״̬��\n");
        hjset_long();
        save();
        return 1;
    }

    write("��ʽ������ֱ������ <mewiz> ָ���ѯ��ȷ�÷���\n");
    return 1;
}


int do_maipiao( )
{
    object me=this_player(),piao,gold;

    if( me->query("balance") < MP_GOLD * 10000 )
        return notify_fail("���Ǯׯ�����Թ���һ����Ʊ����Ʊ�۸��� "+MP_GOLD+" ���ƽ�\n");

    piao = new(__DIR__"other_obj/obj_menpiao");
    me->add("balance", - MP_GOLD*10000);
    piao->move(me);
    message_vision("$N֧����"+chinese_number(MP_GOLD)+"���ƽ�������һ����Ʊ��\n",me);

    in_money += MP_GOLD;
    buy_piao_times ++;

    save();
    return 1;
}

int do_create_room_file()
{
    object me = this_player();
    int last_num;

    if( !wizardp(me) || getuid(me) != "naihe" )
        return notify_fail("��ָ��ֻ���� �κ� ִ�С�\n");

    if( me->query_temp("hj_create_room") != 1 )
    {
        me->set_temp("hj_create_room", 1);
        return notify_fail("��ָ�ֱ�ӽ��� .c �ļ������������ļ���Ϊ��\n "+
__DIR__ + "hj_room1.c  �� "+ __DIR__ + "hj_room"+ HJ_ROOM_AMOUNT+ ".c 
�� "+HJ_ROOM_AMOUNT +" ���ļ��������ȷ�������ٴ����뱾ָ�\n");
    }

    me->delete_temp("hj_create_room");

    if( file_size( HJ_ROOM_CREATE_D +".c" ) < 0 )
        return notify_fail("�޷��ҵ� "+ HJ_ROOM_CREATE_D+" �ļ���\n");

    last_num = HJ_ROOM_AMOUNT;
    write( HJ_ROOM_CREATE_D->create_room( me, __DIR__, last_num ) );
    return 1;
}


int valid_leave(object me, string dir)
{
    object menpiao;
    mapping conditions;
    
    if( dir != "enter" )
        return ::valid_leave(me,dir);
    if( !userp(me) )
        return notify_fail("��ͷ���ý��룡����\n");
    // �������ˣ���Ȼ��һ��NPC���˽�ȥ
    //     if( wizardp(me) ) return ::valid_leave(me,dir);
    // ��ʦ�಻����ѡ�
    if(GAME_OPEN != 1) return notify_fail("��Ϸ��δ���š�\n");
    if( me->query("scheming") )
        return notify_fail("����ִ�����߼ƻ��߲������ڡ�\n");
    if( !interactive(me) )
        return notify_fail("�����߲������ڡ�\n");
    // ������״̬
    conditions = me->query_all_condition();
    if( conditions && sizeof( conditions ) > 0 )
        return notify_fail("����������״���������������ÿ���������������ر���������(family_job)���Ժ����ԡ�\n");
    // �鿴�������
    if( who_in_hj()[ "amount" ] >= MAX_HJ_ENTER )
        return notify_fail("�����Ѿ���̫�����ڻþ����ˣ����Ժ��ٳ��Խ��롣\n");
    if( query("all_ip_in_hj") && sizeof( query("all_ip_in_hj") )
      && member_array( query_ip_name(me), query("all_ip_in_hj") ) != -1
    )
        return notify_fail("�þ����Ѿ�������ͬIP������ˣ�ͬһIPֻ�ܽ���һ����ҡ�\n");
    if( FREE_GAME == 1 )
    {
        in_times++;
        save();
        write("���������������Ϸ���лл������Ϸ��\n");
    }
    else
    {
        menpiao = present("men piao",me);
        if(!menpiao || !menpiao->query("hj menpiao") )
            return notify_fail("���ȹ�Ʊ���������ڡ���鿴�����ϵ�˵����\n");
        destruct(menpiao);
        message_vision("$N�ͳ�һ����Ʊ�����űߵ�С������漴��������˽�ȥ��\n",me);
        in_times++;
        save();
    }
    me->set_temp("hj2003-valid_enter", 1);
    me->delete_temp( "hj2003-enter_timeout" );
    call_out("player_timeout", 180, me);
    return ::valid_leave(me, dir);
}

void player_timeout(object me)
{
    if( !me || !environment(me) || environment(me)->query("room_mark")
      || present("qixing deng",me ) || environment(me) == this_object()
      || strsrch( base_name( environment(me) ), "room_gameover_hj" ) != -1 )
        return;
    if( !me->query_temp( "hj2003-enter_timeout") )
    {
        me->set_temp( "hj2003-enter_timeout", 1);
        tell_object( me, HIR"\n��Ϸ��ʾ���뾡�������Ϸ(xuanze ������������ xuanze feng)�����򽫱��߳���Ϸ��\n\n"NOR );
        call_out( "player_timeout", 180, me);
        return;
    }
    message_vision( "$N��������̫���ˣ���Ȼ�е�һ���𵴣�\n",me);
    me->move( this_object() );
    message_vision( "$N��һ��Ī�������͵������\n",me);
}

void save_player_level( string name, string id, int lv, int time )
{
    player_level_info[ id ] = ([ "name":name, "lv":lv, "time":time ]);
    save();
}

string del_player_level( string id )
{
    if( !id ) return "Ҫ�����һλ��ҵ� level ��¼��\n";
    if( undefinedp( player_level_info[id] ) )
        return "û�������ҵ� level ��¼��\n";

    map_delete( player_level_info, id );
    save();
    return "����ҵ� level ��¼��������� level ��¼�����´ν��뱾��ʱ�������\n";
}
