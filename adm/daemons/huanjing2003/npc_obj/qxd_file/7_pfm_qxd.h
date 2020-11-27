// for all_cmds_qxd_hj.h
// naihe 21:42 03-10-17
// ���������ܶ����� pfm  05-9-3 21:25

mapping can_use_pfm( string pfm_id, object me, object target )
{

    // �ɹ�ʱ������������Ϣ����ս�������е� "pfm_info" �������ա�
    // "name": "����������"
    // "damages": ������
    // "me_busy": ����æʱ
    // "msg_all": �������������˿�������
    // "msg_me": ���Լ���������
    // "msg_target": ������������������
    // "lost_hp": �Լ�������Ϣ
    mapping pfm_list;
    string *pfm_msg, pfm_skills, pfm_name, pfm_limit;
    int LostHP_pfm = 10, Me_busy = 3+random(3);
    // PFM_LvNeed �����ǵ� 1 ���ļ����� #define ���壬�����иõȼ��ļ��ܲ���ʹ�� pfm.
    // ����2������д��ĸ���Լ� PFM_LvNeed ��������Ψһ�ж� pfm ��ʲô�ȼ��ܹ�ʹ�á�
    // �Լ�������Ϣ�����������busy �����ݡ�
    string msg_all, msg_me, msg_target, find_name;
    int damages, damages_skills;
    if( !pfm_id || !me )
        return 0;
    // �����б�
    pfm_list = ([
        "kf": ({ "hfzj", "���", "feng", }),
        "by": ({ "hyzj", "����", "yu",   }),
        "jl": ({ "llzj", "����", "lei",  }),
        "xd": ({ "ydzj", "Ѹ��", "dian", }),
        "dh": ({ "dhzj", "���", 0,      }),
        "hy": ({ "fhzj", "����", 0,      }),
        "js": ({ "gszj", "��ʯ", 0,      }),
        //"cs": ({ "heal", "����", 0,      }),  // ȡ��������о����Ǻܲ���
    ]);
    // �޴˾������ڣ����ز�����
    if( undefinedp( pfm_list[ pfm_id ] ) )
        return ([ "err_msg": "���趨�ľ���������" ]);
    // ��ô�д˾������ڣ��ж��������������Ƿ����
    // �Ƿ񶮵ö�Ӧ���ܣ��Լ����ܵȼ��Ƿ��㹻
    pfm_msg = pfm_list[ pfm_id ];
    pfm_skills = pfm_msg[0];
    pfm_name = pfm_msg[1];
    pfm_limit = pfm_msg[2];
    // �����ü��ܣ����ز�����
    if( !me->query_temp("hj_game_skills/" + pfm_skills )
     || !me->query_temp( "hj_game_damages/" + pfm_skills ) )
        return ([ "err_msg": "�㲢�����á�"+pfm_name+"�������ļ���" ]);
    // ���ȼ��ܱ���ʹ��
    if( pfm_limit && me->query_temp( "hj_game_find" ) != pfm_limit )
        return ([ "err_msg": "��"+pfm_name+"������ֻ���ɱ���������ʹ��" ]);
    damages_skills = me->query_temp( "hj_game_damages/" + pfm_skills );
    // �ȼ��Ƿ��㹻����Ϣ�Ƿ��㹻
    if( damages_skills < PFM_LvNeed )
        return ([ "err_msg":"��ļ��ܵȼ��������޷�ʹ�á�"+pfm_name+"������" ]);
    if( me->query_temp("hj_hp") < ( LostHP_pfm * 5 ) )
        return ([ "err_msg":"�����Ϣ̫�����޷�ʹ�á�"+pfm_name+"������" ]);
    /*
    // ���ˣ�һ��OK������ʹ�þ�����
    // ����ǻָ�����ֱ�������ﴦ��
    if( pfm_id == "cs" )
    {
        int hp_add;
        message_vision( CYN"\nֻ��$N"NOR+CYN"���������һ����������������ö��ˡ�\n\n"NOR, me );
        hp_add = me->query_temp( "hj_game_damages/" + pfm_skills );
        hp_add = hp_add*2 + random(hp_add);
        me->add_temp( "hj_hp", hp_add );
        if( me->query_temp( "hj_hp" ) > me->query_temp( "hj_hp_max") )
            me->set_temp( "hj_hp", me->query_temp( "hj_hp_max") );
        me->start_busy( 3+random(8) );
        return 0;  // return 0 ʱ�Ǳ߾Ͳ��ٴ����ˡ�
    }
    */
    if( pfm_id == "dh" )
    {
        // me ������ζ��� busy
        int target_busy;
        if( target->query_busy() > 3 )
            return ([ "err_msg" : target->query("name")+"��æ�ú��أ����ǳû�������" ]);
        if( me->query_temp( "hj_hp" ) < (50+damages_skills) )
            return ([ "err_msg" : "����Ϣ�������޷�ʩչ��"+pfm_name+"������" ]);
        message_vision( HIB"\nֻ��$N"HIB"��������һ�����������׵�����$n"HIB"�����ƶ���$n"HIB"���Ķ�����\n"NOR, me, target );
        me->add_temp( "hj_hp", -(damages_skills/3+random(damages_skills/5)) ); // 99lv = 33 + 19, 40lv = 16+8
        // ʧ��
        // ��꼼����������Ч��  ��Ч�ֿ������깥��
        if( target->query_temp( "hj_special/sh" ) )
        {
            message_vision( HIB"ֻ����$N"HIB"���ܺ�������һ������֮�������ǰ�$N"HIB"����������һ�㡣\n", target );
        }
        else if( !random(10) || random( 100 )+1 > damages_skills )
        {
            message_vision( CYN"$N"NOR+CYN"һ��֮�¼�æһ�����㿪��$n"NOR+CYN"�Ĺ�����\n\n"NOR, target, me );
        }
        else
        {
            target_busy = 5+random( damages_skills/10 );  // lv40:5+random(4)  lv99:5+random(9)
            tell_object( target, HIR"��һ���ӱ��ĸ����У�ͻȻȫ��Ӳ���޷������� (���æʱ "+target_busy+" ��)\n\n"NOR );
            tell_object( me, HIR+target->query("name")+HIR"���ĸ����У�ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n\n"NOR );
            tell_room( environment(target), HIR+target->query("name")+HIR"���ĸ����У�ͻȻ���۷�ֱ�������˴�ס���Ƶġ�\n\n"NOR, ({ me, target }));
            target->start_busy( target_busy );
        }
        return 0;
    }
    // ȷ������������
    damages = (damages_skills * 2) + random( damages_skills / 5 );
    // lv40 = 80 + random(8)
    // lv99 = 198 + random( 19 )
    // Ч�������������ӳ�
    find_name = me->query_temp( "hj_game_find");

    switch( pfm_name )
    {
      case "���":
        if( find_name == "feng" )
            damages += damages/4;   // lv40 = 100 +, lv99 = 250+
        // ����
        msg_all = HIW"\nֻ��$N"HIW"����ŭĿһ����ͦ������������������������ǰ�������е��������������������\n��ʱ����Ҷ�׷ɣ����ŭ�𣬴�����˷�����$n"HIW"ֱ�˶���������\n\n"NOR;
        msg_me = HIW"\n��˫Ŀһ����ͦ������������������������ǰ�������е��������������������\n��ʱ����Ҷ�׷ɣ����ŭ�𣬴�����˷�����$n"HIW"ֱ�˶���������\n����� "HIG+damages+HIW" ���˺���\n\n"NOR;
        msg_target = HIW"\nֻ��$N"HIW"����˫Ŀһ����ͦ������������������������ǰ�������е��������������������\n��ʱ����Ҷ�׷ɣ����ŭ�𣬴�����˷�������ֱ�˶���������\n����� "HIR+damages+HIW" ���˺���\n\n"NOR;
        break;
      case "����":
        if( find_name == "yu" )
            damages += damages/4;
        msg_all = HIM"\nֻ��$N"NOR+HIM"���ظ�����أ�˫Ŀ΢�գ���������һ�֣����������������֮�꣬�뽽�����°ɣ���\n���ʱ̿ն�ʱ���Ʊ�ǣ���������������֮����һ�ſŶ���׼��$n"NOR+HIM"��Х��ȥ������\n\n"NOR;
        msg_me = HIM"\n�㸡����أ�˫Ŀ������������һ�֣����������������֮�꣬�뽽�����°ɣ���\n���ʱ̿ն�ʱ���Ʊ�ǣ���������������֮����һ�ſŶ���׼��$n"NOR+HIM"��Х��ȥ������\n����� "HIG+ damages + NOR+HIM" ���˺���\n\n"NOR;
        msg_target = HIM"\nֻ��$N"NOR+HIM"���ظ�����أ�˫Ŀ΢�գ���������һ�֣����������������֮�꣬�뽽�����°ɣ���\n���ʱ̿ն�ʱ���Ʊ�ǣ���������������֮����һ�ſŶ���׼�����Х����������\n����� "HIR+ damages +NOR+HIM" ���˺���\n\n"NOR;
        break;
      case "����":
        if( find_name == "lei" )
            damages += damages/4;
        msg_all = HIC"\n��Ȼֻ��$N"NOR+HIC"˫����ǰһ�ƣ���Ȼ�ȵ���������֮�ף��쳹�ķ���������\n�Ĵ�����Ԥ�׵�����ը�����������������ǣ�����ǧ�������Գ�$n"NOR+HIC"��Ϯ��ȥ������\n\n"NOR;
        msg_me = HIC"\n��˫����ǰһ�ƣ���Ȼ�ȵ���������֮�ף��쳹�ķ���������\n�Ĵ�����Ԥ�׵�����ը�����������������ǣ�����ǧ�������Գ�$n"NOR+HIC"��Ϯ��ȥ������\n����� "HIG+ damages + NOR+HIC" ���˺���\n\n"NOR;
        msg_target = HIC"\n��Ȼֻ��$N"NOR+HIC"˫����ǰһ�ƣ���Ȼ�ȵ���������֮�ף��쳹�ķ���������\n�Ĵ�����Ԥ�׵�����ը�����������������ǣ�����ǧ�������Գ��㱼Ϯ����������\n����� "HIR+ damages +NOR+HIC" ���˺���\n\n"NOR;
        break;
      case "Ѹ��":
        if( find_name == "dian" )
            damages += damages/4;
        msg_all = HIG"\n��Ȼֻ��$N"NOR+HIG"����̧��һָ���죬�����黭��Բ���͵�ָ��$n"NOR+HIG"��\n������һָ������ﾹȻ����һ�����磬���ų���������ֱ��$n"NOR+HIG"��ȥ������\n\n"NOR;
        msg_me = HIG"\n��̧�����֣�һָ���죬�����黭��Բ���������ģ��漴ָ��$n"NOR+HIG"��\n��һָ��������Ｔ������һ�����磬���ų���������ֱ��$n"NOR+HIG"��ȥ������\n����� "HIG+damages+NOR+HIG" ���˺���\n\n"NOR;
        msg_target = HIG"\n��Ȼֻ��$N"NOR+HIG"����̧��һָ���죬�����黭��Բ���͵�ָ�����㣡\n������һָ������ﾹȻ����һ�����磬���ų���������ֱ������˹���������\n����� "HIR+damages+NOR+HIR" ���˺���\n\n"NOR;
        break;
      case "����":
        msg_all = WHT"\nֻ����$N"NOR+WHT"������Цһ������������ǰ�黭һԲ��һ����"HIR"����"NOR+WHT"��ƾ�����ɣ��������ˣ�\n�����ţ�$N"NOR+WHT"�ȵ������ţ���˫����˦�����Ż�����ʱ����$n"NOR+WHT"�����ȥ������\n\n"NOR;
        msg_me = WHT"\n�������Цһ������������ǰ�黭һԲ��һ����"HIR"����"NOR+WHT"�ʹ�ƾ�����ɣ��������ˣ�\n�����ţ�������һ�����ţ���˫����˦�����Ż�����ʱ����$n"NOR+WHT"�����ȥ������\n����� "HIG+damages+NOR+WHT" ���˺���\n\n"NOR;
        msg_target = WHT"\nֻ����$N"NOR+WHT"������Цһ������������ǰ�黭һԲ��һ����"HIR"����"NOR+WHT"��ƾ�����ɣ��������ˣ�\n�����ţ�$N"NOR+WHT"�ȵ������ţ���˫����˦�����Ż�����ʱ�����㼤�����������\n����� "HIR+damages+NOR+WHT" ���˺���\n\n"NOR;
        break;
      case "��ʯ":
        msg_all = WHT"\nֻ����$N"NOR+WHT"������Цһ������������ǰ�黭һԲ��һ��"YEL"��ʯ"WHT"��ƾ�����ɣ�\n����$N"NOR+WHT"һ���Ϻȡ��ţ�����ʯ�����޴�ѹ��֮�У�����$n"NOR+WHT"��ȥ������\n\n"NOR;
        msg_me = WHT"\n�������Цһ������������ǰ�黭һԲ��һ��"YEL"��ʯ"WHT"�ʹ�ƾ�����ɣ�\n����һ�����ţ����������˾���ʯ�����޴�ѹ��֮�У�����$n"NOR+WHT"��ȥ������\n����� "HIG+damages+NOR+WHT" ���˺���\n\n"NOR;
        msg_target = WHT"\nֻ����$N"NOR+WHT"������Цһ������������ǰ�黭һԲ��һ��"YEL"��ʯ"WHT"��ƾ�����ɣ�\n����$N"NOR+WHT"һ���Ϻȡ��ţ�����ʯ�����޴�ѹ��֮�У����������˹���������\n����� "HIR+damages+NOR+WHT" ���˺���\n\n"NOR;
        break;
    }
    return ([ "name": pfm_name, "damages": damages, "me_busy": Me_busy,"lost_hp": LostHP_pfm+random(LostHP_pfm),
          "msg_all": msg_all, "msg_me": msg_me, "msg_target": msg_target ]);
}
