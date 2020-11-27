// �����ļ�̫�󣬱��ļ����ֿ������ļ����� room_gameover_hj.c ���á�
// ��ȡ��Ʒ���һ��þ���Ϸ�Ľ�������
// naihe 22:56 03-10-23


// #########################################################
// #########################################################
// #########################################################
// 
// �����ཱƷ����˵����(award_data)
//            "score?"  ����Ҫ���ٵ�ɼ����Զһ�
//            "me?"     ���ܹ�������
//            "dt-n?"   ����������
//            "c-name"  ������������2-4���֣����򲻶��루������ѿ���
//            "all->0?" ���Ƿ���ܶ���һ��
//
// �� gxd Ϊ�����÷ֱ�����100�����ϲſ��Զһ������ҽ��� 100:1 �Ķһ��ʼ���ó�
//              ���Եõ����ٵ� gxd. ���� "all->0?" �� "yes"����ô�����һ�����ͷ
//              ����ȫ���������������֮����ұ� set("shenzhou/pts", ����)��
//
// ע�⣬���� "gxd", "pot" ��λ�õ�ID����ǰ8���ַ���Ч��
// �� ���׶ȡ�����ֵ ��λ�õ�����������ǰ8���ַ���Ч����4�����֣���
//
// ����ཱƷ����˵���������ཱƷ�Ѳ����ţ���غ�����ɾ������
//             ����ͬ�ϣ�ֻ�Ƕ���һ�� "fl-set"��
//             ����ʾ���ƽ�������֮ǰ��Ҫ�ȶ��������һЩʲô���� set.
//             ���� hsw, ������ã� hsw->set("huanjing2003_award", 1);
//             ����Ҫ�κ�����ʱ���ɲ�Ҫ "fl-set" ��� "fl-set" ��ֵ���ա�
//
// ���⽱Ʒ����˵����
// #define ��2����ֵ�������⽱Ʒ����Ҫ�ĵ÷�ֵ���ֱ��ǣ�
// 
//      KEEP_SKILLS_SCORE, һ�α�������
//      KEEP_POWER_SCORE,  һ�α�������
//
// #########################################################
// #########################################################
// #########################################################


// ��������������������������
// ��������������������������
// ��������������������������


#define        KEEP_SKILLS_SCORE        500
#define        KEEP_POWER_SCORE         500

#define        award_data        ([ "gxd": ([ "score?":300,"me?":1,"dt-n?":"shenzhou/pts", "c-name":"���׶�","all->0?":"yes" ]),"exp": ([ "score?":1,  "me?":3,"dt-n?":"huanjing2003/exp","c-name":"�þ�����","all->0?":"yes" ]),"pot": ([ "score?":1,  "me?":1,"dt-n?":"huanjing2003/pot","c-name":"�þ�Ǳ��","all->0?":"yes" ]), ])

#define        award_obj    ([ ])

// ��������������������������
// ��������������������������
// ��������������������������



string get_prize_name( string n, string id )
{
    if( !n ) n = "���ؽ���";
    if( !id ) id = "??????";
    if( strlen( n ) > 8 ) n = n[0..7];
    if( strlen( id ) > 8 ) id = id[0..7];

    return sprintf( "%s(%s)", n, id );
}


int prize(string arg)
{
    object me = this_player(), temp_obj;
    int amount, temp_int, my_score, i;
    string msg, *key, temp_str;
    mapping award_all, temp_map;

    if( GetAward != "����" )
        return notify_fail("��ȡ��Ʒ�ĳ����ѱ���ʦ�رգ����ԵȻ�ѯ��������ʦ��\n");

    if( query("is_checking") == me->query("id") )
        return notify_fail("�������ڼ�����ĵ÷֣����Ե����콱��\n");

    if( me->query_temp("huanjing") )
        return notify_fail("������ <YEAH> ָ�����÷֣������콱��\n");


    my_score = me->query_temp("hj_score");

    // �������ʱ���ر����á�
    if( IS_TEST )
    {
        if( !TEST_AWARD_GXD )
            return notify_fail("�����ǲ����ڼ䣬����û���κν�������ֱ���뿪���ɡ�\n");

        if( !arg || ( arg != "gxd" && arg != "leiji" ) )
            return notify_fail("�����ǲ����ڼ䣬����С�����������ʹ�������ĵ÷��� "+my_score+" �㡣\n"
                "��ȡ���׶ȣ�<YEAH!!! gxd>  --> �������е÷ֻ��ɹ��׶ȣ�ÿ 500 ��÷ֿɵ� "+TEST_AWARD_GXD+" �㡣\n"
                "��ȡ�ۻ����ܣ�<YEAH!!! leiji> --> �������е÷ֻ���ʹ���ۻ����ܵĻ��ᡣÿ 1000 �㻻��һ�Ρ�\n");

        if( arg == "gxd" )
        {
            me->delete_temp("hj_score");
            amount = my_score / 500 * TEST_AWARD_GXD;
            message_vision("$N�ĵ÷�Ϊ "+my_score+" �㣬��ȡ�� "+amount+" �㹱�׶ȡ�\n",me);
            me->add("shenzhou/pts", amount );
            return 1;
        }

        me->delete_temp( "hj_score" );
        amount = my_score / 1000;
        message_vision("$N�ĵ÷�Ϊ "+my_score+" �㣬��ȡ�� "+amount+" ��ʹ���ۻ����ܵĻ��ᡣ\n",me);
        me->add("huanjing2003/last_skills_times", amount);
        if( me->query("huanjing2003/last_skills_times") > 9 )
        {
            message_vision( "$N���ۻ�����ʹ�ô������������ֻ��ʹ�� 9 �Ρ�\n",me);
            me->set("huanjing2003/last_skills_times", 9 );
        }
        return 1;
        // test ״̬�����콱 LOG��
    }
    // �ã�����״̬�µ��콱����
    // �����з�û�֣����Կ���Ʒ��
    if( me->is_busy() ) return notify_fail("�㻹æ���أ����п����콱�ɡ�\n");
    me->start_busy( 1 );

    if( !arg )
    {

        msg = HIC"=====================================================================
        ���þ���ңԶ��˵֮��Ե���������֡�    ���������б�\n\n"NOR;

        award_all = award_data + award_obj;
        key = keys( award_all );
        if( key && sizeof( key ) > 0 )
        {
            for( i=0;i<sizeof(key);i++ )
            {
                temp_map = award_all[ key[i] ];
                // ����һ�³��ȣ�Ư��Щ
                temp_str = get_prize_name( temp_map["c-name"], key[i] );
                msg += sprintf( "%s %-18s ---- %|4d �÷ֿɻ� %|4d \"%s\"��\n",
                    temp_map[ "all->0?" ] == "yes" ? "��" : "��",
                    get_prize_name( temp_map["c-name"], key[i] ),
                    temp_map[ "score?" ], temp_map[ "me?" ],
                    temp_map[ "c-name"] );
            }
        }

        msg += sprintf("
\"��\"��Ǳ�ʾ����ȡ�ý�ʱ������ĵ÷ְ��һ��ʼ���󣬿ɵõ���Ӧ
              ����Ľ�Ʒ����ʣ�µġ���ͷ���÷ֽ��ᱻ�����
\"��\"��Ǳ�ʾ����ȡ�ý�ʱ���۳���Ʒ��Ҫ�ĵ÷ֺ�ʣ�µĵ÷�����Ч��

"HIW"���� %s "HIW"ָ���콱���㻹�� %d ��ĵ÷֡�
"HIY"�ر����б����� %s "HIY"ָ���ѯ��
"HIC"=====================================================================\n"NOR,
            HIR"<YEAH!!! ID>"NOR, my_score,
            HIR"<YEAH!!! sp>"NOR,
            );

        me->start_more( msg );
        return 1;
    }

    if( arg == "sp" )
    {
        msg = sprintf( HIC"=====================================================================
        ���þ���ңԶ��˵֮��Ե���������֡�    �ر����б�"NOR"

    ����ÿһ���˳��þ���Ϸ��һ������÷֣�������һ�ε����м��ܺ�
�������ᱻ��¼����ÿһ�������þ���Ϸʱ����Щ��¼���ᱻ���������У�

    ���м��ܼ�¼����Ϊ���֮�ģ���������ƣ�1 �����������ü��ܣ�
                                    ���κμ���ʱ���ָ�Ĭ�����ã�
    ����    ��¼����Ϊ�ķ�֮������� 30 �㣬5 �������ʱ�ָ�Ĭ�����á�

    ������������Ե÷ֶһ��������ʹ����Щ�ۻ�ֵ�Ļ��ᡣ���㻹ӵ��ĳ
��Ļ���ʱ�����������Ϸ�󣬸����ۻ�ֵ��ֱ��Ӧ�õ���Ϸ�ж�����ȡĬ��
�����á����ǣ�����㻹��ĳ����������ȴû���˸�����ۻ���¼�������
ֵ̫�ͣ����ʹ�û���Ĵ������ᱻ�ۼ�����ʹ��Ĭ�����á�

�� ���ܱ���(skills)  -----  �� %|4d ��÷ֻ�ȡ 1 �λ��ᣬ��� 9 �Ρ�
�� ��������(power)   -----  �� %|4d ��÷ֻ�ȡ 1 �λ��ᣬ��� 9 �Ρ�

"HIW"���� %s "HIW"ָ���콱���㻹�� %d ��ĵ÷֡�
"HIY"��ļ���/������¼���� <YEAH!!! last> ��ѯ��
"HIC"=====================================================================\n"NOR,
            KEEP_SKILLS_SCORE, KEEP_POWER_SCORE, 
            HIR"<YEAH!!! ID>"NOR, my_score );

        write( msg );
        return 1;
    }
    // ��ѯ�ѱ���¼�˵ĸ���ֵ��(δ����)
    if( arg == "last" )
    {
        msg = sprintf(  "===============================================\n"
                "���������¼Ϊ %d �㣬���� %d ��ʹ�õĻ��ᡣ\n",
                    me->query("huanjing2003/last_power"),
                    me->query("huanjing2003/last_power_times") );

        temp_map = me->query("huanjing2003/last_skills_lv");
        if( !temp_map || !sizeof(temp_map) )
            msg += "��û�м��ܼ�¼��\n";
        else
        {
            msg += "��ļ��ܼ�¼����(���� "+me->query("huanjing2003/last_skills_times")+" ��ʹ�õĻ���)��\n";
            key = keys( temp_map );
            for( i=0;i<sizeof( key ); i++ )
            {
                msg += sprintf( "%s\t%s\t\t%d\n",
                    key[i],
                    !me->query("huanjing2003/last_skills_name")[key[i]] ?
                        "��Ч����" :
                    me->query("huanjing2003/last_skills_name")[key[i]],
                    temp_map[key[i]] );
            }
        }

        msg += "===============================================\n" +
            "��Щ��ֵ����������һ�ν���þ���ʱ�򣬱�ϵͳ�Զ�������\n"+
            "������㻹��ĳ���ʹ�û��ᣬ�����Լ���ʹ��(���������)��Ӧ����Ŀ��\n";

        me->start_more( msg );
        return 1;
    }

    if( my_score < 1 )
        return notify_fail("��û���κε÷֣��޷��콱��\n");

    switch( arg )
    {
        case "skills": temp_int = KEEP_SKILLS_SCORE; temp_str = "�ۻ�����"; break;
        case "power": temp_int = KEEP_POWER_SCORE; temp_str = "�ۻ�����"; break;
    }

    if( arg == "skills" || arg == "power" )
    {
        if( my_score < temp_int )
            return notify_fail("��ĵ÷ֲ��� "+temp_int+" �㣬�޷���ȡ��"+temp_str+"���Ľ�����\n");

        if( me->query("huanjing2003/last_"+arg+"_times") >= 9 )
            return notify_fail("������ 9 �λ�����ʹ�á�"+temp_str+"���Ļ����ˡ�\n");

        // OK�����Ի�
        me->add("huanjing2003/last_"+arg+"_times", 1 );
        me->set_temp("hj_score", my_score - temp_int );

        message_vision( "$N�� "+temp_int+" ��÷ֻ�����һ�Ρ�"+temp_str+"���Ļ��ᡣ\n", me);
        hj_log_file( sprintf("\n%s(%s)�콱--\"%s\"1��(��%d��)��(%s)\n",
            me->query("name"), getuid(me), temp_str, temp_int, ctime_format() ) );
        return 1;
    }
    // ��������ͨ��Ʒϵ�С�
    // �ж������ཱƷ��
    if( !undefinedp( award_data[arg] ) )
    {
        temp_map = award_data[arg];
        // "gxd": ([ "score?":100,"me?":1,"dt-n?":"shenzhou/pts", "c-name":"���׶�","all->0?":"yes" ]),
        if( my_score < temp_map[ "score?" ] )
            return notify_fail("��ĵ÷ֲ�������ȡ������\n");
        temp_str = temp_map[ "c-name" ];
        // һ���콱
        if( temp_map[ "all->0?" ] == "yes" )
        {
            // ������콱����
            temp_int = my_score / temp_map[ "score?" ];
            // ����ý�����
            temp_int *= temp_map[ "me?" ];
            // LOG
            message_vision( sprintf("$N�����еĵ÷�������ȡ�� %d ��%s��\n",
                temp_int, temp_str), me );
            hj_log_file( sprintf("\n%s(%s)�콱--\"%s\"%d��(һ����%d��)��(%s)\n",
                me->query("name"), getuid(me), temp_str, temp_int, 
                me->query_temp("hj_score"), ctime_format() ) );
            // ����
            me->add( temp_map[ "dt-n?" ] , temp_int );
            me->delete_temp("hj_score");
            return 1;
        }
        // ��һ���콱
        // �������
        temp_int = temp_map[ "me?" ];
        // ����� my_score �����Ѹģ���Ϊ�콱��Ҫ�ĵ÷�ֵ��
        my_score = temp_map[ "score?" ];
        message_vision( sprintf( "$N�� %d ��÷ֻ�ȡ�� %d ��%s��\n",
            my_score, temp_int, temp_str), me);
        hj_log_file( sprintf("\n%s(%s)�콱--\"%s\"%d��(��%d��)��(%s)\n",
            me->query("name"), getuid(me), temp_str, temp_int, 
            my_score, ctime_format() ) );
        me->add( temp_map[ "dt-n?" ] , temp_int );
        me->add_temp( "hj_score", -my_score );
        return 1;
    }
    write("û�������Ʒ�������� <YEAH!!!> ��ѯ��ͨ����� <YEAH!!! sp> ��ѯ�ر��\n");
    return 1;
}
