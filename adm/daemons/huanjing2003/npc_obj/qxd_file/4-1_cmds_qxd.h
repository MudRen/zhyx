// ֧�ֻþ��ڻ���ָ��
// ��һ���ļ�д�����ˣ�д��������
// ��ָ��ο� cmd i ��д
// ʵ��˵����ϸ�ؿ��� i ָ����� hj ��ʵ�ڴ��пɾ���֮����sigh
// naihe 6:39 03-11-5
string get_msg( object *list, int type )
{
    mixed class123;
    object *temp;
    int n, i=0;
    string msg = "  ";

    if( !list || sizeof(list) < 1 ) return "";

    // �Ƚ��д�����ͬһ��������ֳɸ�С��
    class123 = unique_array( list, (: sprintf( "%s%s%s",
            base_name($1), $1->name(), $1->query("id") ) :) );

    // ��ʼ��֯����Ϣ
    foreach( temp in class123 )
    {
        // �Դ˷�������ÿ���ſ��г� 2 �� 3 �����֣���Լ��Ļ��
        i++;
        if( i>3 && type ) { i=1;msg += "\n  "; }
        if( i>2 && !type ) { i=1;msg += "\n  "; }
        // ����Ϊ 0 ʱ��2��һ���ţ����� 3��һ����

        n = sizeof(temp);
        msg += sprintf( "(%2s)%s  ", n<10 ? "0"+n : ""+n, temp[0]->short() );
    }

    return msg;
}


int do_gi()
{
    object *inv, me = this_player(), *temp, *hjinv, *list;
    int n;
    string msg, cl;

    // ��ʱ�����ѯ
//    if( !me_ok(me) ) return 0;

    inv = all_inventory(me);
    if( !inv || sizeof(inv) < 1 )
        return errs("������û��Я���κζ�����\n");

    // �õ�һ�� object �飬������ֻ���� ��query("hj_game/obj")��Ϣ���κ����
    hjinv = filter_array( inv, (: $1->query("hj_game/obj") :) );

    // ���޸��飬��ֱ�ӷ���
    if( !hjinv || !sizeof(hjinv) )
        return errs( "�㹲Я��"+chinese_number(sizeof(inv))
                +"��������Ʒ����û���κλþ�����Ʒ��\n");
    // ����ͷ��Ϣ
    msg = sprintf(HIC"
�㹲Я�� %d ����ʽ��Ʒ�������� %d%% ��
������ %d ��������Ʒ��%d ���þ�����Ʒ��
=======================================================================\n"NOR,
        sizeof(inv),
        me->query_encumbrance() * 100 / me->query_max_encumbrance(), 
        sizeof(inv)-sizeof(hjinv), sizeof(hjinv) );

    cl = HIY;

// ��ʼ������ϸ�ķ���ͳ�ơ�

    // ������
    list = filter_array( hjinv, (: $1->query("hj_game/obj") == "sword" :) );
    // ����н����࣬��֯����Ϣ������Щ�����б����޳�
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"����������(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // ħ��ˮ����
    list = filter_array( hjinv, (: $1->query("hj_game/obj") == "magic" :) );
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"ħ��ˮ����(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // ����ʯ��
    list = filter_array( hjinv, (: $1->query("hj_game/obj") == "quest" :) );
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"����ʯ��(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // ������
    list = filter_array( hjinv, (: $1->query("hj_game/obj") == "tools" :) );
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"����������(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // ��Ʒ��ʯ��
    list = filter_array( hjinv, (: $1->query("hj_game/obj") == "other" :) );
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"��Ʒ��ʯ��(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( list, 1 ) );
        hjinv -= list;
    }

    // Ȩ�ȡ����屦����
    list = filter_array( hjinv, (: $1->query("hj_game/obj") == "the_gem"
                  || $1->query("hj_game/obj") == "the_gem_qz" :) );
    if( n = sizeof( list ) )
    {
        msg += sprintf( cl+"���屦����(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( list, 0 ) );
        hjinv -= list;
    }

    // �������ʣ�࣬��Ϊ������
    if( n = sizeof( hjinv )  )
        msg += sprintf( cl+"������(�� %d ��)��\n"NOR"%s\n",
                n, get_msg( hjinv, 0 ) );

    msg += HIC"=======================================================================\n"NOR;
    write( msg );
    return 1;
}

// ��ʱ�뿪��Ϸ
int do_hjleave(string arg)
{
    object me = this_player();
    if( !me_ok(me) )
        return errs( "ʲô��\n");
    if( !arg || arg != "yes" )
        return errs( 
            "�����ڻþ���Ϸ����Ҫ��ʱ�뿪ʱ����ʹ�����ָ�\n"
            "���ָ������������Ϸ��ɫ�ܵ������������ܵ������κη���Ĺ�����\n"
            "�������������һЩ��Ϸ���ݻ������������Ϸ��ʱ�䵽�����������Ϸ���ȵȡ�\n"
            "ÿ����Ϸ��ֻ��ʹ���������ָ�ʹ��ʱ��������ڿ���״̬�¡�\n"
            "\n          �����ȷʵ����ʱ�뿪�������룺 hjleave yes\n\n"
        );
    if( me->query_temp( "hjleave_usetimes" ) >= 3 )
        return errs( "������Ϸ���Ѿ��ù�������� 3 ���ˡ�\n");
    if( me->is_busy()
      || me->query_temp("hj_healing")
      || me->query_temp("hj_fighting")
      || me->query_temp("hj_need_waiting")
    )
        return errs( "�㻹æ���أ�������ڿ���ʱ����ʹ�����ָ�\n");
    if( environment(me)->query("room_mark") == 1 )
        return errs( "�㲻���� 1 �ŵص�ʹ�����ָ�\n" );
    me->add_temp( "hjleave_usetimes", 1 );
    new( __DIR__"hj_temp_leave") -> move(me);
    return 1;
}
