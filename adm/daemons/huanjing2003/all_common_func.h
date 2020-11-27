// ���ļ��� all_room_info_hj.h
// �� 1_room_info_special.h 
// ��ͬ���á�

// naihe 0:33 03-10-21



void reset()
{ 
    ::reset();
    set("no_clean_up", 1); 
}

int block_cmds()
{
    write("�þ��ﲻ����ʹ�����ָ����� hj ��ʹ�õ�һЩ����ָ������� help hj2003 ��ѯ��\n");
    return 1;
}

int do_look(string arg)
{
    string *orention;

    if( !arg )
        return 0;
    orention=({ "east","west","south","north",
        "northeast","northwest","southeast","southwest"
    });
    if( member_array( arg , orention ) != -1 )
    {
        write("��������һƬ���֣��㿴����Զ���������\n");
        return 1;
    }
    return 0;
}

int do_get(string arg)
{
    if( !arg || arg != "all")
        return 0;
    write("����һ��һ���ؼ�ա�\n");
    return 1;
}

void get_out_here( object me )
{
    if( !me ) return;

    message_vision( HIR"$N"HIR"��֪��ô�Ĵ����˻þ������һ��������𵴰�$N"HIR"���˳�ȥ��\n"NOR,me);
    me->move( __DIR__"room_door_hj" );
    message_vision("һ��Ī�����𵴺������ţ�$N��֪��ô�ľͺ��س����������ˡ�\n",me);
}


void full_all( object me )
{
    if( !me )
        return;
    me->set("jingli",me->query("max_jingli") ); // ֻҪ��Щ��������·ʱ���ģ��Լ����ֶ����������ˡ�
    me->set("food", 50 );
    me->set("water",50 );
}

int valid_leave(object me, string dir)
{
    string temp;

    if( me->query_temp("hj_move_busy") > 1000 )
        return notify_fail("������������أ����޷�����̫�졣\n");

    temp = me->query_temp("hj_need_waiting");
    if( temp && me->is_busy() )
    {
        switch(temp)
        {
            case "healing":return notify_fail("�����������أ��߲�����\n");
            case "fighting":return notify_fail("�㻹��ս���У�����ס���߲�����\n");
            default:return notify_fail("����æ���أ��޷��뿪��\n");
        }
    }

    if( me->query_temp("hj_the_orention") == dir && random( 10 ) == 1 &&
        !me->query("hj_game/npc") )
    {
        call_out("games_random_move",1, me);
        message_vision( HIR"\nһ��������𵴺�Ȼ��������\n"NOR, me );
        me->start_busy(2);
        return notify_fail("\n");
    }

    // ��· busy ��ʽ���ģ���� ���ǵ� ��ʵ���µ�Ч����
    // ���ǵ��н�����ֵ����ݼ��ĺ�����
    // ��֮������������Ч��  ��·ʱæʱ�ϵ�
    if( !me->query("hj_game/npc") )
    {
        if( me->query_temp("hj_game_find") == "feng" )
            me->add_temp("hj_move_busy", (150+random(100)) );  // ����ǿ
        else me->add_temp("hj_move_busy", (300+random(200) ) );
    }

    me->set_temp("hj_the_orention",dir); //  ��¼��һ���ķ���

    return ::valid_leave(me, dir);
}

void games_random_move( object me )
{
    object rooms;
    string random_rooms;

    if( !me || !environment(me) || environment(me) != this_object() ) return;
    random_rooms=__DIR__"hj_room"+( 2 + random( HJ_ROOM_AMOUNT-1 ));

    tell_room( environment(me), HIR+me->query("name")+HIR"ͻȻƾ����ʧ������\n"NOR, ({ me }) );
    rooms=find_object(random_rooms);
    if(!rooms) rooms = load_object(random_rooms);
    if( !rooms ) rooms = this_object();
    this_player()->move(rooms);
    message_vision(HIG"$N"HIG"��һ����ֵ����͵�����������\n"NOR,me);
}

