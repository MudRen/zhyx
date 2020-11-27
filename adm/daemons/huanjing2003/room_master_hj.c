//                ��׼��������ʾ��                                   |
// ���þ���Ѱ��ϵ������֮���صص�
// by naihe  2002-10-22
// ��ʦ���� <mewiz> ָ�����һЩ��Ϸ��صĲ��������������� <mewiz> ��ѯ��
// ǿ��������� �þ� �����ڴ���֮������Ʒ���������֮���һ�У�����ɾ����
//   ָ�� �� <mewiz del_all>   �����ʹ�ã�����
// ������һ������  naihe 8:35 03-11-3

// naihe 05-9-7 10:35  V1.7 ��������

#include <ansi.h>
inherit ROOM;

#include    "npc_obj/hj_settings/obj_list.h"
// ���߼�NPC�б�

#include    "npc_obj/hj_settings/room_amount_hj.h"
// ���������Ʒʱ����Ҫ�õ�������һ������ �þ��ܷ����� HJ_ROOM_AMOUNT

int is_gameing = 0;
// ��Ϸ��ǰ״̬������δ������

#define        KILL_NPC_DISPERSION_TIME     180
#define        KILL_NPC_AMOUNT_MIN          1
#define        KILL_NPC_AMOUNT_RANDOM       3
// ������������ϵͳ��ÿ�� TIME ���ӣ�����Ϸ�ڼ���  MIN + random( RANDOM ) ��
// ɱ¾�͵�NPC��
// ���ڵ������� 3 ���� 1-3 ���� 15:18 03-10-18


#define        QUEST_NPC_DISPERSION_TIME    600
// ����ʱ��͸���Ϸ�з���һ������� "quest" ��NPC��
// �����ˡ���ͯ�����ˡ��ؽ������鱦�͵�

#define        ROUND_DISPERSION_TIME        900
// ÿ��һ��ʱ��û������ҽ��� hj����ô�б�Ҫ����һЩ��Ʒ�Է�ֹ�䳡��
#define        ROUND_DISPERSION_AMOUNT_MIN      20
#define        ROUND_DISPERSION_AMOUNT_RANDOM   6
// �����������Χ�� MIN + random( RANDOM )


int dispersion( object me );
int del_all( object me );
void random_dispersion_to_hj( string *dis_list, int times );
void clean_hj();


void c_msg( string msg )
{
    object naihe;
    if( !msg ) return;
    naihe = find_player( "naihe" );
    if( !naihe || !userp(naihe) || naihe->query("env/no_hj_wizmsg") )
        CHANNEL_D->do_channel( this_object(), "sys", YEL+ msg + NOR);
    else tell_object( naihe, HIR"���þ�ϵͳ֪ͨ����"+msg + "\n"NOR );
}

void create()
{
    set("short",MAG"���֮��"NOR);
    set("long","

      �� �� �� �� �� �� �� �� ���� �� ��(enter) �ɡ���

\n");

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "enter":__DIR__"room_readygo_hj",
    ]));

    set("channel_id", HIY"���þ��������ġ�"NOR);
    setup();
}

void init()
{
    if(wizardp(this_player())) add_action("do_mewiz","mewiz");
    add_action("do_nocmds", ({ "scheme", "drop", "put"}) );
}

int do_nocmds()
{
    write("�����ֹʹ�����ָ�\n");
    return 1;
}

void reset()
{ 
    ::reset(); 
    set("no_clean_up", 1); 
}

int valid_leave(object me, string dir)
{
    if(dir == "enter")
    {
        if( !userp(me) )
            return notify_fail("��ͷ�������ڡ�\n");

        //if( !me->query_temp("enter_hj") )
            //return notify_fail("��ӻþ����Ž�������ſ��Լ���������һ���ط���\n");

        // �������
        // �����Ϸδ�����������������������
        if( !is_gameing )
        {
            remove_call_out("start_game");
            call_out("start_game",1);
        }
        // ������Σ�ÿ��һ��ʱ������·���һ����Ϸ�������Ʒ��С��
        // ����������ҽ��룬�����ʱ�����¿�ʼ
        // ���Ҹú������жϣ�������ʱ���Ƿ���Ϸ״̬(!is_gameing)���򲻲�����
        remove_call_out("dispersion_again");
        call_out("dispersion_again", ROUND_DISPERSION_TIME );

        // 1����Сʱ����Ϸ����Ϊ���ر��С���ͬʱ�������г�����Ʒ
        // ����������ҽ��룬�����ʱ�����¿�ʼ
        remove_call_out("reset_game");
        call_out("reset_game",6600);

        // ������ʲô���
        if( !is_gameing )
            return notify_fail("���Ե����룬�þ���Ϸ���������С���\n");
    }
        return ::valid_leave(me, dir);
}


int dispersion( object me )
{
    int times;

    if( !me || !wizardp(me) ) return 0;
    if( !is_gameing )
    {
        tell_object(me, "��Ϸ״̬������ ������ �����������ɷ������\n");
        return 1;
    }

    times = 50 + random(11);
    tell_object( me, "Ok. ��ִ�к����������� sys ��Ϣ��\n");
    CHANNEL_D->do_channel( me, "sys", sprintf("%s �ֶ�ִ�лþ���Ϸ���������ɷ�����������(%d �����)��", me->query("id"), times));
    random_dispersion_to_hj( obj_list_all, times );
    return 1;
}


int del_all( object me )
{
    if( !me || !wizardp(me) ) return 0;

    tell_object( me, "Ok. ��ִ�к����������� sys ��Ϣ��\n");
    CHANNEL_D->do_channel( me, "sys", sprintf("%s �ֶ�ִ�лþ���Ϸ�������ĵ�ǿ��������о������������", me->query("id") ));
    clean_hj();
    return 1;
}

int do_mewiz(string arg)
{
    object me = this_player();

    if( !arg )
    {
        write("
��ʹ��֮ǿ��ָ�

<mewiz dispersion>      ����ɷ� 50 -60 �������Ʒ���������������
                            ��ָ��ֻ���� is_gameing ״̬(��Ϸ������) �ſ���ʹ�á�
<mewiz del_all>         ǿ��������� �þ� ���з����ڴ��ڵ��������ҳ��⣩
                            ��ָ�ֱ�Ӹ�����Ϸ״̬Ϊ !is_gameing ��

��ؽ���ʹ�ã�\n");
        return 1;
    }

    if( arg == "dispersion" )
        return dispersion(me);

    if( arg == "del_all" )
        return del_all(me);

    write("ָ��������ֱ������ <mewiz> ָ������ѯ��\n");
    return 1;
}


// Ϊ�˱��������������Ϸ���ã��������NPCɱ��JOB����������䳡��
// �������������һ��ʱ��󽫻����±����������
void dispersion_again()
{
    int times;
    
    remove_call_out("dispersion_again");
    if( !is_gameing )
        return;
    // ������Ƿ�����״̬���ͱ���
    times = ROUND_DISPERSION_AMOUNT_MIN + random( ROUND_DISPERSION_AMOUNT_RANDOM );
    c_msg( "�þ���Ϸ���� "+(ROUND_DISPERSION_TIME/60)+" ����������ҽ��룬���ڸ����ڵص㲹�������߻�����(��"+times+"��)��");
    random_dispersion_to_hj( obj_list_all, times);
    call_out("dispersion_again", ROUND_DISPERSION_TIME );  // һ��ʱ�������
}

// ��Ϸ����
void start_game()
{
    int times;

    if( is_gameing ) return;
    // ��������������������������������������ף����������ϲ��ᷢ��

    times = 50+random(21);

    c_msg( "�þ���Ϸ�Զ�����������������ླ���������" );
    remove_call_out("clean_hj");
    clean_hj();
    c_msg( "�þ���Ϸ�Զ����������ڸ����ڵص㷢�Ÿ�����߻�����(��"+times+"��)����");
    random_dispersion_to_hj( obj_list_all, times);
    is_gameing = 1;

    // ��ʼ���ϵط���ɱ¾��NPC
    remove_call_out("random_dispersion_killer");
    call_out("random_dispersion_killer", 1);

    // ��ʼ���ϵط��š��ر����͵�NPC
    remove_call_out("random_dispersion_questnpc");
    call_out("random_dispersion_questnpc", 1);

    remove_call_out("reset_game");
    call_out("reset_game", 6600 );
}


void reset_game()
{
    c_msg( "�þ���Ϸ�Ѿ�100�������˽����ˣ����Զ�������������������ָ���ϷΪ��δ��������" );
    clean_hj();
}


// ����������ڲ��ϵ����þ������ quest �� npc
void random_dispersion_questnpc()
{
    if( !is_gameing ) return;
    random_dispersion_to_hj( ({ __DIR__"npc_obj/hj_npc_quest" }), 1 );

    remove_call_out("random_dispersion_questnpc");
    call_out("random_dispersion_questnpc", QUEST_NPC_DISPERSION_TIME );
}


// ����������ڲ��ϵ����þ������ɱ¾��NPC
void random_dispersion_killer()
{
    if( !is_gameing ) return;
    random_dispersion_to_hj( ({ __DIR__"npc_obj/hj_npc_kill" }),
        KILL_NPC_AMOUNT_MIN + random( KILL_NPC_AMOUNT_RANDOM ) );

    remove_call_out("random_dispersion_killer");
    call_out("random_dispersion_killer", KILL_NPC_DISPERSION_TIME );
}

// �˺������������������������������ֱ��� ����б� �� ����(�������)
// ִ�д˺���ʱ�������Զ����С�������������������
void random_dispersion_to_hj( string *dis_list, int times )
{
    int i;
    string r, msg;
    object rs, obj;

    if( !dis_list || sizeof(dis_list) < 1 ) return;

    i = times;
    while( i-- )
    {
        r = __DIR__"hj_room"+( 1+random(HJ_ROOM_AMOUNT) );
        rs = find_object( r );
        if( !rs ) rs = load_object( r );

        // ���ﲻ���� file_size ���жϡ�
        obj=new( dis_list[random(sizeof(dis_list))] );
        obj->move(rs);
        if(obj->query("msg")) msg=obj->query("msg");
        else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room( r ,msg);
    }

    if( times < 10 ) return; // ����� killer �ķ���Ҳ��ͣ�ر�

    c_msg( "�þ���Ϸ������������ϣ������� "+times+" ����ʽ��Ʒ��NPC��" );
}

// �˺�������þ����硣
void clean_hj()
{
    int i,j, c1, c2;
    string f, *files;
    object ob;

    is_gameing = 0;
    // ֱ�ӻָ���Ϸ״̬Ϊ ��δ������
    for( i = 1; i <= HJ_ROOM_AMOUNT; i++ )
    {
        ob = find_object(__DIR__"hj_room"+i);
        if(!ob)
            continue;
        destruct( ob );
        c1 ++;
    }
    // ɾ���������
    files = get_dir( __DIR__"npc_obj/");
    foreach( f in files )
    {
        f = __DIR__ "npc_obj/" + f;
        if( f[<2..<1] != ".c" )
            continue;
        if( (ob = find_object( f )) )
        {
            destruct( ob );
            c2 ++;
        }
    }
    c_msg( "�þ���Ϸ��������������� "+c1+" ���������ڴ�ķ��䣻"+c2+" ����Ϸ�ο��������Ϸ�ָ�Ϊ��δ������״̬��" );
}
