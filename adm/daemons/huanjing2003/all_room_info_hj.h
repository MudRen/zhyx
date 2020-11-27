//                ��׼��������ʾ��                                   |

void delete_exit();
void back_exit();
void add_exit();
void back_exit2();
void full_all( object me );

string the_exit;
string the_exit2;

#include    "npc_obj/hj_settings/room_amount_hj.h"


void create()
{
    set("room_mark",mark);
    set("short",MAG"�þ�"NOR+GRN"����ʧ֮��������֮��"NOR);

    set("long","������һƬ�������ߵ����֣���Ϣȴ���ǹŹ֡���Χ����ľ���ߴ��׳��֦
�پ��ᣬ����������¹�������ΧҲ������Ϣ�����µ���������ľ�ĸ������Ӿ�
������ò����ײ���ǿ̤�ü���С�����Ĵ�ͨȥ��\n");

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

// �����Ƕ�Ӧ�ĳ��ڡ�

    set("exits",([
        "east":__DIR__"hj_room"+( mark +1),
        "west":__DIR__"hj_room"+( mark -1),
        "south":__DIR__"hj_room"+( mark +10),
        "north":__DIR__"hj_room"+( mark -10),
        "northeast":__DIR__"hj_room"+( mark -9),
        "northwest":__DIR__"hj_room"+( mark -11),
        "southeast":__DIR__"hj_room"+( mark +11),
        "southwest":__DIR__"hj_room"+( mark +9),
    ]));

    if( mark <= 10 ) // �����ͷ��䣬������һ���� ���� ����
    {
        if(query("exits/north")) delete("exits/north");
        if(query("exits/northeast")) delete("exits/northeast");
        if(query("exits/northwest")) delete("exits/northwest");
    }

    if( (mark % 10) == 1 ) // �����ͷ��䣬�����һ���� ���� ����
    {
        if(query("exits/west")) delete("exits/west");
        if(query("exits/southwest")) delete("exits/southwest");
        if(query("exits/northwest")) delete("exits/northwest");
    }

    if( (mark % 10) == 0 ) // �����ͷ��䣬���ұ�һ���� ���� ����
    {
        if(query("exits/east")) delete("exits/east");
        if(query("exits/southeast")) delete("exits/southeast");
        if(query("exits/northeast")) delete("exits/northeast");
    }

    if( mark >= (HJ_ROOM_AMOUNT - 9) ) // �����ͷ��䣬������һ���� ���� ����
    {
        if(query("exits/south")) delete("exits/south");
        if(query("exits/southeast")) delete("exits/southeast");
        if(query("exits/southwest")) delete("exits/southwest");
    }

// �ܹ��ķ�������������ʮ����

    set("all_exit","ok");


// �������� 1 �ŷ��䣬�������ļ�֧��
// ����������£�

// ��һ�����һ���������֧������ָ���NPC�������Ͻǣ���������
    if( mark == 10 )
        set("objects", ([ __DIR__"npc_obj/hj_npc_zhujian" : 1 ]));

// ���һ���һ���������֧����ħָ���NPC�������½ǣ����Ϸ���
    if( mark == HJ_ROOM_AMOUNT - 9 )
        set("objects", ([ __DIR__"npc_obj/hj_npc_lianmo" : 1 ]));

// ���һ������ķ������֧�ֽ���ָ��� NPC�������½ǣ����Ϸ���
    if( mark == HJ_ROOM_AMOUNT )
        set("objects", ([ __DIR__"npc_obj/hj_npc_trader" : 1 ]));

    setup();
}


void init()
{
// ���еĹ��ж���(�� all_room_info_hj.h �� 1_room_info_special.h ����)
#include "all_common_init.h"

    if( this_object()->query("all_exit") == "ok" )
    {
        if( !random(3) ) delete_exit();
        else if( !random(2) ) add_exit();
    }
}

// ���еĹ��к���(�� all_room_info_hj.h �� 1_room_info_special.h ����)
#include "all_common_func.h"


void delete_exit()
{
    string *the_exits;

    if( query("all_exit") != "ok" ) return;


    the_exits = ({    "east", "west", "north", "south",
        "northeast", "northwest", "southeast", "southwest", });

    the_exit = the_exits[ random(8) ];

    if( query("exits/"+ the_exit) )
        delete( "exits/" + the_exit );
    else the_exit = "none";

    if(the_exit != "none")
    {
        set("all_exit","be_delete");
        if(random(3) == 1) message("vision",HIB"���ƺ�����������ľ��λ���ƶ���һ�£�����\n"NOR,this_object());
        remove_call_out("back_exit");
        call_out("back_exit",30+random(90));
    }
}

void back_exit()
{
    int temp;
    mapping the_marks;

    if( query("all_exit") == "ok" || query("all_exit") != "be_delete" )
        return;

    temp = mark;

    the_marks = ([
        "east"        : temp + 1,
        "west"        : temp - 1,
        "south"        : temp + 10,
        "north"        : temp - 10,
        "northeast"    : temp - 9,
        "northwest"    : temp - 11,
        "southeast"    : temp + 11,
        "southwest"    : temp + 9,
    ]);

    if( !undefinedp( the_marks[ the_exit ] ) )
        set( "exits/" + the_exit , __DIR__"hj_room" + the_marks[ the_exit ] );

    if(random(3) == 1) message("vision",HIB"���ƺ�����������ľ��λ���ƶ���һ�£�����\n"NOR,this_object());
    set("all_exit","ok");
}

void add_exit()
{
    string temp_add_exit, *the_exits;

    if( query("all_exit") != "ok" ) return;

    the_exits = ({    "east", "west", "north", "south",
        "northeast", "northwest", "southeast", "southwest", });


    the_exit2 = the_exits[ random(8) ];
    temp_add_exit=__DIR__"hj_room"+(1+random( HJ_ROOM_AMOUNT ));

    if( !query("exits/"+ the_exit2) )
        set( "exits/"+ the_exit2, temp_add_exit );
    else the_exit2 = "none";

    if( the_exit2 != "none" )
    {
        set("all_exit","be_add");
        if(random(3) == 1) message("vision",HIB"���ƺ�����������ľ��λ���ƶ���һ�£�����\n"NOR,this_object());
        remove_call_out("back_exit2");
        call_out("back_exit2",30+random(90));
    }
}

void back_exit2()
{
    if( query("all_exit") == "ok" || query("all_exit") != "be_add" )
        return;

    delete( "exits/" + the_exit2 );

    if(random(3) == 1) message("vision",HIB"���ƺ�����������ľ��λ���ƶ���һ�£�����\n"NOR,this_object());
    set("all_exit","ok");
}

