
int do_gpfm( string arg )
{
    object me = this_player();
    if( !me_ok(me) )
        return 0;
    if( !arg )
        return errs("��׼��ʹ��ʲô������\n");
    if( me->query_temp("hj_need_waiting") == "fighting" || me->query_temp("hj_fighting") )
    {
        set("pfm_ready", arg);
        write("��ĬĬ�۾���׼���������� ��"+arg+"�� ��\n");
        return 1;
    }
    write("����ֻ����ս��ʱ������\n");
    return 1;
}

int do_gbei( string arg )
{
    object me = this_player();
    string now_bei, msg;

    if( !me_ok(me) ) return 0;

    now_bei = me->query_temp("hj_bei");
    if( !now_bei ) now_bei = ".";
    if( now_bei == "." || now_bei == "hand" || now_bei == "none" )
        msg = "ͽ�ֹ���";
    else
    {
        if( strsrch( now_bei , "zj" ) != -1 )
            msg = "ʹ�ü��� ��"+now_bei+"��";
        else msg = "ʹ�õ��� ��"+now_bei+"��";
    }

    if( !arg ) return errs( "��ָ������������ս����ʹ�õķ�ʽ����ɼ�Ϊ <bb> ��
���磺 gbei bs jian , ��ս���н�����Ѱ�������Լ����ϵ�IDΪ\"bs jian\"��
       ���ߣ���Ŀ����е��߸�����ʽ�Ĺ�����
���磺 gbei hfzj , ��ս���н����Լ��ܡ�����֮��������Ŀ����м��ܹ�����

������������磺 gbei jian , ��ô���������� \"jian\" ���ID�ĵ���ʱ��
�������ʹ��������������

�����������õķ�ʽ�Ѿ��޷�ʵ�֣����Զ�ʹ�ÿ��ֹ�������������ûᱻ������

�����ϣ���Կ��ֹ����������ã� <gbei .>  ���� <gbei hand> �� �� <gbei none>��
��Ҫ�鿴�Լ��Ѿ����õ�״̬�������� <gbei ?> ָ�

���������õķ�ʽ�ǣ�"+ msg + " \n");

    if( arg == "?" )
        return errs("������׼���õ�ս����ʽ�ǣ�"+ msg + " \n");

    me->set_temp("hj_bei", arg );
    now_bei = me->query_temp("hj_bei");
    if( now_bei == "." || now_bei == "hand" || now_bei == "none" )
        msg = "ͽ�ֹ���";
    else
    {
        if( strsrch( now_bei , "zj" ) != -1 )
            msg = "ʹ�ü��� ��"+now_bei+"��";
        else msg = "ʹ�õ��� ��"+now_bei+"��";
    }
    write("���ս����ʽ׼��Ϊ�� "+ msg +" ��\n");
    return 1;
}

// gk ��ʽ���£�ʵ���Զ��򶷣������������
int do_gk(string arg)
{
    //    object me,target,tools;
    //    int damages,me_busy,me_power,target_busy;
    //    string tools_name,target_name,do_att="no",color_name,temp,skills_name,skills_name2;

    object me = this_player(), target;
    string target_id;

    if( !me_ok(me) ) return 0;

    if(!arg) return errs("����Ҫ����˭��\n");

    if( me->query_temp("hj_need_waiting") == "healing" || me->query_temp("hj_healing") )
            return errs("�㻹�������أ�Ҫ��ܵ���ͣ����(halt / ht)��\n");

    target = present( arg, environment(me) );

    if(!target) return errs("����û������ˡ�\n");
    if(!target->is_character()) return errs("�ⲻ�ǻ��\n");
    if(!target->query_temp("hj_hp") || target->query_temp("hj_hp") <1 )
        return errs(target->query("name")+"û��˿���þ������Ϣ�����ع����˰ɡ�\n");
    if(!living(target)) return errs("�����Ϸ����������ѵĶ��ֲ��ܹ�����\n");
    if(target == me ) return errs("�����Լ���û��Ҫ�ɡ���\n");

/*  �����κ���Ҷ�ɱ��
// �Լ��÷ֲ���������ɱ���
    if( me->query_temp("hj_score") < 200 && !target->query("hj_game/npc"))
        return errs("�����Ϸ�÷���ô�ͣ�����ץ��ʱ��Ū����ȥ�ɣ�\n");

// ������ɱ�÷ֵ͵����
    if( target->query_temp("hj_score") < 200 && !target->query("hj_game/npc"))
        return errs(target->query("name")+"����Ϸ�÷�̫�ͣ�����������̫�ðɣ�\n");
*/


    if( me->query("gender") == "����" )
        message_vision(HIR"\nֻ����$N"HIR"��ȵ���������������������$n"HIR"���ϱ㹥��\n\n"NOR, me, target );
    else if( me->query("gender") == "Ů��" )
        message_vision(HIR"\nֻ����$N"HIR"һ���ú����������ɣ���������$n"HIR"���ϱ㹥��\n\n"NOR, me, target );
    else message_vision(HIR"\nֻ����$N"HIR"������һЦ�������򻰣�����$n"HIR"���ϱ㹥��\n\n"NOR, me, target );


    me->set_temp("hj_fighting", target );
    me->set_temp("hj_need_waiting", "fighting");

    // ���ﲻ�� remove_call_out(), ��Ϊ�ú��������жϾ䣬����� call_out ��������
    call_out("fighting", 1);
    return 1;
}

// ��Ŀ�����һ�ι���
void do_attack( object me, object target, int damages )
{
    string describe;
    if( !objectp(me) || !objectp(target) || damages < 1 )
        return;
    // ��ν��������
    if( !random(50) )
    {
        message_vision( HIR"��Ȼһ��"HIY"���"HIR"������$N"HIR"��һ����������ǿ��������\n"NOR, me );
        damages *= 2+random(2);
    }
    // ��NPCʱ
        if( target->query("hj_game/npc") )
        {
            // NPC������������
                target->set("killme_by",me->query("id"));
        // ���Եõ��÷֡�
        // ��֮���ȱ�������Ч��  ս���е÷�����
        if( me->query_temp("hj_special/gm") )
            me->add_temp("hj_score",1+random( damages / 8 ));
        else
            me->add_temp("hj_score",1+random( damages / 10 ));
    }
    target->hj_get_attack(me);  // Ŀ��ִ��һ���ܵ������ĺ�����ֻ�� hj npc �����������
    target->add_temp("hj_hp",-damages);  // ��Ŀ���Ѫ
    // ��ʾ����״̬
    describe = get_health_desc( target->query_temp("hj_hp"), target->query_temp("hj_hp_max") );
    message_vision(NOR"�� $N"+describe+NOR" ��\n"NOR,target);
    // ��ϡ�
}

void fighting()
{
    object me = query("my_master"), inv_me, inv_target, target, use_tools, srl;
    string figh_type, fight_use, use_skills, color_name, skills_name, describe, temp;
    int damages, me_busy, me_power, target_busy;

    mapping pfm_info;

    if( !me || !me_ok(me) ) return;

    // �������ʽ(halt)��
    // ������Ӳ��У��к�С�ļ��ʻ���ɴ���
    //    if( !me->query_temp("hj_fighting") || me->query_temp("hj_need_waiting") != "fighting")
    // ��Ϳ����� :)
    if( !me->query_temp("hj_need_waiting")
     || me->query_temp("hj_need_waiting") != "fighting")
        return;

    target = me->query_temp("hj_fighting");
    if( !target || environment(me)->query("room_mark") == 1 )
        return hj_halt( HIW"\n$N"HIW"����һ����ʽ��ͣ��������\n\n"NOR );

    // Ŀ������ң���������������
    if( !target->query("hj_game/npc") &&
        ( !target->query_temp("huanjing")
        || target->query_temp("huanjing")!="start"
        || !target->query_temp("hj_hp") || target->query_temp("hj_hp") <1
        || !target->query_temp("hj_hp_max") ) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );

    // Ŀ�겻����ң�������
    if( target->query("hj_game/npc") && 
        ( !target->query_temp("hj_hp") || target->query_temp("hj_hp") < 1 ) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );

    inv_target = environment( target );
    if( !inv_target || inv_target != environment(me) || !inv_target->query("room_mark") )
        return hj_halt( HIW"\n$N"HIW"��"+target->query("name")+HIW"�Ѳ��ڴ˴�������һ����ʽ������������\n\n"NOR );

    // Ŀ��Я��������
    if( (srl=present("shenren ling",target)) )
    {
        message_vision( CYN"$N"NOR+CYN"���ϵ�"+srl->query("name")+NOR+CYN"ͻȻ����һ���â��\n"NOR, target );
        return hj_halt( HIB"$N"HIB"����һ��Ī���ľ޴�ѹ����ֻ�ð���������\n"NOR );
    }
    // Ŀ���뿪��Ϸ
    if( present( "hj temp leave obj", target ) )
    {
        return hj_halt( CYN"$n"NOR+CYN"���κ������֣����Ʋ���ʵ��һ�㣡$N"NOR+CYN"ֻ�ð���������\n"NOR );
    }
    // �õģ�����׼����ʼ����Ŀ�ꡣ
    // æʱ�У��ȴ���һ�롣
    if( me->is_busy() )
    {
        remove_call_out("fighting");
        call_out("fighting", 1);
        return;
    }
    // ���Դ��ˣ��жϴ����ʽ
    // ����
    if( !me->query_temp("hj_bei") )
        me->set_temp("hj_bei", "hand");

    figh_type = ".";

    // �о������������ж�
    if( query("pfm_ready") )
    {
        // �ú��������жϲ�������Ϣ��
        pfm_info = can_use_pfm( query("pfm_ready"), me, target );
        // �Ѿ�������ɾ��
        delete( "pfm_ready" );
        // �������0���򲻼������κδ���
        if( !mapp(pfm_info) || !sizeof(pfm_info) )
        {
            remove_call_out("fighting");
            call_out("fighting", 1);
            return;
        }
        // ������ʱ����������ʾ��Ϣ "err_msg" �����һ����ʾ
        // ������ sizeof() Ϊ 7 �����ݲ��������ġ�
        if( sizeof( pfm_info ) != 7 )
        {
            if( !pfm_info || undefinedp( pfm_info[ "err_msg" ] ) )
                tell_object( me, "�������⣬�޷�ʹ�þ�����\n");
            else tell_object( me, pfm_info[ "err_msg" ] + "��\n");
        }
        // �����޴�������ʹ�ø� pfm ��
        // �±ߵ����������У�����ȫʹ�� pfm_info ���ṩ�����ݡ�
        else figh_type = "pfm";
    }
    // ��ʼ�ж����������
    // ����趨����
    fight_use = me->query_temp("hj_bei");

    if( figh_type == "." &&
      (!fight_use || fight_use == "." || fight_use == "hand" || fight_use == "none")
    )
        figh_type = "hand";
    // ��������δȷ�������������жϡ��ж��Ƿ������͡�
    // �Ȳ鿴���޸ü��ܣ��Լ��Ƿ���Ϣ����
    if( figh_type == "." )
    {
        if( fight_use != "heal"
          && me->query_temp( "hj_game_skills/" + fight_use )
          && me->query_temp( "hj_game_damages/"+ fight_use )
        )
        {
            // �м��ܣ������Ϣ�Ƿ����
            if( me->query_temp("hj_hp") < 100 )
            {
                message_vision( HIY"\n$N"HIY"��Ȼ������Ϣ��˳��ֻ�÷������ܹ��������ÿ�����ս��\n\n"NOR, me);
                figh_type == "hand";
                // ǿ�Ƹ�������ͽ��ս��
                me->set_temp("hj_bei", "hand");
            }
            // ��ôOK��ʹ�ü���
            else
            {
                use_skills = fight_use;
                figh_type = "skills";
            }
        }
        // �޸���ܣ��������ϵĵ���
        else
        {
            use_tools = present( fight_use, me );
            // ֻ��ʹ�����ϵģ�Ҫ�þ�Ҫ��������
//            if( !use_tools ) use_tools = present( fight_use, environment( me ) );
            // �޸õ��ߣ�������ս
            if( !use_tools ) figh_type = "hand";
            else
            {
                // �ҵ��ˣ�Ҫ���ǲ����ܴ�ܵĶ���
                // �ǵ��ߵ��ǲ������õģ�ת����
                if( !use_tools->query("hj_game/obj")
                 || !use_tools->query("use_times") || !use_tools->query("power")
                 || !use_tools->query("busy") 
                 ||  ( use_tools->query("hj_game/obj") != "sword"
                    && use_tools->query("hj_game/obj") != "magic" ) )
                    figh_type = "hand";
                // ����Ϊ���á�
                else figh_type = "tools";
            }
        }
    }

    // ��ֹδ֪�Ĵ�����������˵�������
    if( figh_type != "tools" && figh_type != "skills" && figh_type != "pfm" )
        figh_type == "hand";
    // **********************************
    // ���ˣ�����������ͽ��й���
    // ������ҵ�������ȷ������������
    if(!me->query_temp("hj_game_mepower"))
        me->set_temp("hj_game_mepower",5);
    me_power = me->query_temp("hj_game_mepower");

    // ��֮���ȱ�������Ч��  ս����������������
    if( me->query_temp("hj_special/ll") )
        me_power = (me_power*2) + random(me_power);
    // ͽ�ֹ���
    if( figh_type == "hand" )
    {
        // ȷ����������æʱ��
        damages = (me_power * 3 / 4 + random(me_power / 4) );
        me_busy = 2;
        // ��������
        temp = ({
            "�ӳ�һȭ",
            "�߳�һ��",
            "����һ��",
            "����һײ",
            "����һ��",
        })[ random(5) ];
        // ��ʹ�� message_vision() �ķ�ʽ
        tell_room(environment(me),CYN"\n"+me->query("name")+NOR+CYN"������"+target->query("name")+NOR+CYN+temp+"��\n"NOR,({me,target}));
        tell_object(target,CYN"\n"+me->query("name")+NOR+CYN"��������"+temp+"������� "HIR""+damages+""NOR+CYN" ����˺���\n"NOR);
        tell_object(me,CYN"\n�������"+target->query("name")+NOR+CYN+temp+"������� "HIG""+damages+""NOR+CYN" ����˺���\n");
        if( !random(me->query_temp("hj_game_mepower") * 2) )
        {
            write(HIY"��ֻ���ô�ȭ�Ź�����ˣ������ƺ��ִ���Щ��\n"NOR);
            me->add_temp("hj_game_mepower",1 );
        }
    }
    // �õ��߹���
    if( figh_type == "tools" )
    {
        // ������ʲô���͵ĵ�����
        // ����
        if( use_tools->query("hj_game/obj") == "sword" )
        {
            // ��ȷ����������æʱ��
            damages = ( me_power *3 / 4 + random( me_power / 4 ) ) +
                  ( use_tools->query( "power" ) *3 / 4 ) + 
                  random( use_tools->query( "power" ) / 4 );

            if( use_tools->query("busy") == 888 ) me_busy = 0;
            else me_busy = use_tools->query("busy");
            use_tools->add("use_times",-1);
            // �ж� use_tools ʹ�ô�����϶�Ҫ delete �ľ��ӷ��ں�ߣ�
            // �����ʱ delete ���������滹Ҫ���ã�����BUG BUG��
            // �ã���������
            temp = ({ "��", "��", "��", "��", "��" })[ random(5) ];
            tell_room(environment(me),CYN"\n"+me->query("name")+NOR+CYN"����"+use_tools->query("name")+NOR+CYN"��"+target->query("name")+NOR+CYN+temp+"ȥ��\n"NOR,({me,target}));
            tell_object(target,CYN"\n"+me->query("name")+NOR+CYN"����"+use_tools->query("name")+NOR+CYN"����"+temp+"��������� "HIR+damages+NOR+CYN" ����˺���\n"NOR);
            tell_object(me,CYN"\n������"+use_tools->query("name")+NOR+CYN"��"+target->query("name")+NOR+CYN+temp+"ȥ������� "HIG+damages+NOR+CYN" ����˺���\n");
        }
        // ������ħ��ˮ����
        else
        {
            // ȷ����������
            damages = ( me_power * 3 / 4 + random( me_power / 4 ) ) +
                  ( use_tools->query( "power" ) * 3 / 4 ) + 
                  random( use_tools->query( "power" ) / 4 );
            if( use_tools->query("type") == query("find_name") )
                damages *= 2+random(2);
            if( use_tools->query("busy") == 888 ) me_busy = 0;
            else me_busy = use_tools->query("busy");
            use_tools->add("use_times",-1);
            switch(use_tools->query("type"))
            {
                case "��֮����": color_name=HIW;break;
                case "��֮����": color_name=HIM;break;
                case "��֮����": color_name=HIC;break;
                case "��֮����": color_name=HIG;break;
                default:color_name = WHT;
            }
            message_vision(color_name+"\n$N"NOR+color_name+"����$n"NOR+color_name+"��������������ħ�����֣���\n"NOR,me, use_tools);
            tell_room(environment(me),color_name+"ֻ��"+use_tools->query("att_msg")+"��"+target->query("name")+NOR+color_name+"��ȥ������� "HIG+damages+NOR+color_name+" ����˺���\n"NOR,target);
            tell_object(target,color_name+"ֻ��"+use_tools->query("att_msg")+"���㹥��������� "HIR+damages+NOR+color_name+" ����˺���\n"NOR);
        }
    }

    // ���ܹ���
    if( figh_type == "skills" )
    {
        // ȷ����������æʱ��
        // ����һ������ĵط���ʹ�ü���ʱ���ֻ���������� 1/2
        damages = me_power / 4 + random( me_power / 4 ) +  
            ( me->query_temp( "hj_game_damages/"+use_skills ) * 3 / 4 ) + 
              random( me->query_temp( "hj_game_damages/"+use_skills ) / 4 );

        skills_name = me->query_temp("hj_game_skills/"+use_skills);
        me_busy = 2+random(2);

        switch( query("find_name") )
        {
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2 ;   // 1.5 ��
                break;
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2;
                break;
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2;
                break;
            case "��֮����":
                if(skills_name == "����֮��")
                damages += damages / 2;
                break;
        }
        if(skills_name == "�ɻ�֮��" || skills_name == "��ʯ֮��")
            damages = 1+(damages/3)+random(damages*2);

        switch( skills_name )
        {
            case "����֮��" : color_name = HIW; break;
            case "����֮��" : color_name = HIM; break;
            case "����֮��" : color_name = HIC; break;
            case "����֮��" : color_name = HIG; break;
            default: color_name = WHT; break;
        }
        tell_room(environment(me), color_name + "\n"+me->query("name")+NOR+color_name+"����"+skills_name+"����"+target->query("name")+NOR+color_name+"��ȥ��\n"NOR,({me,target}));
        tell_object(target,color_name+"\n"+me->query("name")+NOR+color_name+"����"+skills_name+"�����㹥��������� "HIR+damages+NOR+color_name+" ����˺���\n"NOR);
        tell_object(me,color_name+"\n������"+skills_name+"����"+target->query("name")+NOR+color_name+"��ȥ������� "HIG+damages+NOR+color_name+" ����˺���\n"NOR);

        me->add_temp( "hj_hp", -(3+random(3)) );
        // ʹ�ü��ܣ�ÿ�ν������������HP���㡣
        // �л���õ������������Ѷȸ�����
        if( !random( me->query_temp("hj_game_damages/"+use_skills) * 2 ) )
        {
            me->add_temp("hj_game_damages/"+use_skills,1);
            if(me->query_temp("hj_game_damages/"+use_skills) > 99)
                me->set_temp("hj_game_damages/"+use_skills,99);
            else tell_object(me,HIY"��ԡ�"+skills_name+"��������ֽ���һ�㣡\n"NOR);
        }
    }
    // ��������
    if( figh_type == "pfm" )
    {
        // ��������ʱ������������ȫ�ɾ��������ж�������ֻ�Ǽ��������Ļ���������
        // ���������Ļ�����������ʹ�ü���ʱһ�������ֻ���������� 1/2
        damages = me_power / 4 + random( me_power / 4 ) + pfm_info[ "damages" ];
        me_busy = pfm_info[ "me_busy" ];
        me->add_temp( "hj_hp", - pfm_info[ "lost_hp" ] );
        // ����
        temp = replace_string( pfm_info[ "msg_all" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_room(environment(me), temp, ({ me, target }) );

        temp = replace_string( pfm_info[ "msg_me" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_object( me,temp );

        temp = replace_string( pfm_info[ "msg_target" ] , "$N", me->name(1) );
        temp = replace_string( temp, "$n", target->name(1) );
        tell_object( target, temp );
    }
    // ���ˣ����е�����ʲô�Ķ��㶨��
    // ���� ��׼�����������й�����
    // ################################################
    do_attack( me, target, damages );
    // ################################################
    // ��֮���ȱ�������Ч����ս����busy������͡�
    if( me->query_temp("hj_special/xk") && me_busy )
        me->start_busy(1);
    // �����������㡣
    else
        me->start_busy(me_busy);
    // �ر�ļ��ܻ���ߣ���Է���æʱ
    if( figh_type == "skills" && skills_name =="���֮��" )
    {
        me->add_temp( "hj_hp", -(3+random(3)) );
        // ����ʹ�ö��֮������������Ҫ�������Ϣ��
        // ���֮�����⼼������֮��(1)����Ч�ֿ�������ҵĶ���๥����æʱЧ��
        if( !target->query_temp("hj_special/sh") && !random(10)
            && target->query_busy() < 6 )
        {
            // 99 lv ��꼼����� 20 ��æʱ
            target_busy = me->query_temp("hj_game_damages/dhzj") / 5;
            if(target_busy < 2) target_busy = 2;
            target->start_busy( target_busy + target->query_busy() );
            tell_room( environment(me), sprintf( HIR"%s"HIR"ͻȻ���۷�ֱ�������˴�ס���Ƶġ�\n"NOR, target->name(1)), ({me,target}));
            tell_object( target, HIR"��ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
            tell_object( me, HIR+target->name(1)+HIR+"ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
        }
    }
    // ���֮�����⼼������֮��(2)����Ч�ֿ�������ҵĶ���๥����æʱЧ��
    if( !target->query_temp("hj_special/sh") && !random(5)
        && figh_type == "tools" && target->query_busy() < 6
        && (use_tools->query("id") =="dh sj" || use_tools->query("id")=="dh jian" )  )
    {
        target_busy = 10+random(11);
        target->start_busy( target_busy + target->query_busy() );
        tell_room( environment(me), sprintf( HIR"%s"HIR"ͻȻ���۷�ֱ�������˴�ס���Ƶġ�\n"NOR, target->name(1)), ({me,target}));
        tell_object( target, HIR"��ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
        tell_object( me, HIR+target->name(1)+HIR+"ͻȻ���۷�ֱ�������˴�ס���Ƶġ� (���æʱ "+target_busy+" ��)\n"NOR );
    }
    // ������ж��Ƿ�Ҫ delete use_tools.
    if( figh_type == "tools" && use_tools && use_tools ->query("use_times") <= 0 )
        use_tools->delete_me();
    // �㶨��
    // ��֮������������Ч��  ս���п��ܸ��ӹ���
    if( random(8) == 2 && me->query_temp( "hj_game_find" ) == "dian" )
    {
        message_vision( GRN"��Ȼ��֪����������һ��"BLINK+HIG"����"NOR+GRN"����$N"NOR+GRN"��������У�\n"NOR, target );
        damages = (me->query_temp( "hj_game_damages/ydzj" )/2);
        if( damages < 5 )
            damages = 5;
        if( damages > 20 )
            damages = 20;
        // ���� ��׼�����������й�����
        // ################################################
        do_attack( me, target, damages );
        // ################################################
    }
    // �����ټ�һ���жϣ�����Է����ˣ�ֱ�Ӿ� return �ˡ�
    // Ŀ������ң���������������
    if( !target->query("hj_game/npc") &&
        ( !target->query_temp("huanjing")
        || target->query_temp("huanjing")!="start"
        || !target->query_temp("hj_hp") || target->query_temp("hj_hp") <1
        || !target->query_temp("hj_hp_max") ) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );
    // Ŀ�겻����ң�������
    if( target->query("hj_game/npc") && 
        ( !target->query_temp("hj_hp") || target->query_temp("hj_hp") < 1 ) )
             return hj_halt( HIW"\n$N"HIW"����һ����ʽ������$n"HIW"����һЦ��ͣ��������\n\n"NOR );

    // ���ˣ�ѭ�� :)
    // ����Ǹ��ر�ĵ��ߣ�Ѹ��֮������ֱ�ӵ�����һ�Σ������ȴ�1��
    if( figh_type == "tools" && use_tools && use_tools->query("id") == "xy jian" )
    {
        fighting();
        return;
    }
    remove_call_out("fighting");
    call_out("fighting", 1);
    return;
}

