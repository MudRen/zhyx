// hj �ڻ���ָ��

int do_who_in_hj()
{
    object rooms;
    mapping info;

    rooms = find_object( HJ_DIR+ "room_door_hj" );
    if( !rooms ) rooms = load_object( HJ_DIR + "room_door_hj" );
    if( !rooms ) return errs("������������޷���ѯ��\n");
    write( rooms->who_in_hj()[ "info" ] );
    return 1;
}

int do_hjtop()
{
    object out_room;

    out_room = find_object( HJ_OUT_ROOM );
    if( !out_room )
        return errs("�����޷��鿴��¼��\n");
    write(HIW"
       ���þ���ңԶ��˵֮��Ե���������֡�
"+out_room->get_TOP_pic()+"\n"NOR);
    return 1;
}

// ��BUG 55555555 �Ѹ����������Ż���һ���¡�  naihe 2:36 03-10-24
// ������� pah (xsmarter) �Ľ��飬�����˷������ܵ�ָ�
// �����б�ʽ����Ȼ��֮ǰ�ķ��������ܹ������ҵ���Ҫ������
int do_gsks( string arg )
{
    object me = this_player();
    int i, amount, temp;
    string *key, msg, clcl, cl, pic, lv_pic, t1, t2;
    mapping all_skills, all_damages;

    string *list;


    if( !me_ok(me) ) return 0;

    all_skills = me->query_temp("hj_game_skills");
    all_damages = me->query_temp("hj_game_damages");

    if( !all_skills || !mapp(all_skills) || sizeof(all_skills) < 1 ||
        !all_damages || !mapp(all_damages) || sizeof(all_damages) < 1 )
        return errs("�㲢δѧ���κ� �þ� �ڵļ��ܡ�\n");

    if( !arg ) arg = ".";

    if( sscanf(arg, "-d %s", msg) )
    {
        if( undefinedp( all_skills[msg] ) || undefinedp( all_damages[msg] ) )
            return errs("�㲢����������þ��ڵļ��ܡ�\n");

        arg = all_skills[msg];
        me->delete_temp("hj_game_skills/"+msg );
        me->delete_temp("hj_game_damages/"+msg );
        me->delete( "huanjing2003/last_skills_name/"+ msg );
        me->delete( "huanjing2003/last_skills_lv/"+ msg );
        me->save();
        message_vision( "$N���˼��ܣ����Լ������õġ�"+arg+"��ɢȥ�ˡ�\n",me);
        return 1;
    }

    // ���濪ʼ�Թ̶������г���������õļ��ܡ�
    list = ({ "heal", "hfzj", "hyzj", "llzj", "ydzj", "dhzj", "fhzj", "gszj", });


    clcl = NOR + WHT;
    pic = "��";
    msg = clcl +
          "�q���������������Щ��Щ����������Щ����������Щ������������������r\n" +
          "��    ��   ��   ��LV�� ����(yun)�� ����(pfm)��    Ч     ��     ��\n" +
          "�����������������੤�੤���������੤���������੤������������������\n";


    for( i=0;i<sizeof(list);i++ )
    {
        if( undefinedp( all_skills[list[i]] ) || undefinedp( all_damages[list[i]] ) )
            continue;

        // ��ɫ�����⼼��ʾ��������ʾ
        cl = "";
        t1 = "   ----   ";
        t2 = "   ----   ";
        switch( list[i] )
        {
            case "heal" : cl = CYN; t1 = "����(kz)"; break;
            case "hfzj" : cl = HIW; t1 = "���(xk)"; t2 = "���(kf)"; break;
            case "hyzj" : cl = HIM; t1 = "����(cm)"; t2 = "����(by)"; break;
            case "llzj" : cl = HIC; t1 = "����(ll)"; t2 = "����(jl)"; break;
            case "ydzj" : cl = HIG; t1 = "��â(gm)"; t2 = "Ѹ��(xd)"; break;
            case "dhzj" : cl = HIB; t1 = "�ػ�(sh)"; t2 = "���(dh)"; break;
            case "fhzj" : cl = HIR; t1 = "����(rq)"; t2 = "����(hy)"; break;
            case "gszj" : cl = HIY; t1 = "Ѱʯ(xs)"; t2 = "��ʯ(js)"; break;
        }

        // ��Ч����ǣ�����һ�ۿ��Կ����Ƿ���yun, pfm �Լ����ܸߵ�
        if( all_damages[list[i]] > 99 )
            all_damages[list[i]] = 99;
        // ��һ��ʵ���Ϻ� me->set_temp() ͬ��Ч����Ī�� mapping Ҳ�����ơ�ָ�롱�ģ�
        // ���磺 mapping test = objecttt->query("lalala");
        //        objecttt->delete("lalala");
        // ��ô���ʱ�� lalala ��ֵ��Ҳ��Ϊ��0���ˣ���֮��Ȼ��
        temp = all_damages[list[i]];

        if( t1 != "   ----   " )
        {
            if( temp >= YUN_LvNeed ) t1 = "��" + t1;
            else t1 = "��" + t1;
        }
        if( t2 != "   ----   " )
        {
            if( temp >= PFM_LvNeed ) t2 = "��" + t2;
            else t2 = "��" + t2;
        }
        lv_pic = "";
        while( temp>9 )
        {
            lv_pic += pic;
            temp -= 10;
        }
        if( strlen(lv_pic) > 18 ) lv_pic = lv_pic[0..17];

        msg += sprintf( clcl+"��%s%s(%s)"+clcl+"��%2d"+clcl+"��%-10s"+clcl+"��%-10s"+clcl+"��"+cl+"%-18s"+clcl+"��\n"+clcl,
            cl, all_skills[list[i]],list[i], 
            all_damages[list[i]],t1, t2, lv_pic );
        // �������� +1
        amount ++;
    }

    // Ϊ�˽��������չʱ��Ҳ������ʾ�¼���
    // ��һ��δ���ƣ���Ҫ���ӵ���ʲô�����ٿ��Ǹ��ġ�
    key = keys( all_damages );
    for( i=0; i<sizeof( key ); i++ )
    {
        // ����ǰ�洦����ˣ����߼���������������
        if( member_array(key[i],list) != -1 || undefinedp( all_skills[ key[i] ] ) )
            continue;
        // ��������ɫ����
        msg += sprintf( clcl+"��%s(%s)"+clcl+"��%2d"+clcl+"��%-10s"+clcl+"��%-10s"+clcl+"��"+cl+"%-18s"+clcl+"��\n"+clcl,
            all_skills[key[i]], key[i], 
            all_damages[key[i]], "   ----   ","   ----   ","");
            amount ++;
    }
    // û��ͨ�����ļ���
    if( !amount )
        return errs("�㲢δѧ���κ� �þ� �ڵļ��ܡ�\n");
    msg += clcl+ "�t���������������ة��ة����������ة����������ة������������������s\n"NOR;
    write( "  ��������ѧ�õĻþ��ڼ���(��"+chinese_number(amount)+"��)��\n" + msg + "  ����Ҫ����ĳ��ܣ���ʹ��ָ�<gsks -d ������>  ���磺gsks -d heal\n  ��ע�⣬����ָ�ֱ�ӷ����ü��ܣ����޷��ָ���\n");
    return 1;
}

int do_ghp()
{
    object me=this_player();
    string color, temp, temp2, temp3;
    int hp,hp_max, iii;

    if( !me_ok(me) ) return 0;

    hp=me->query_temp("hj_hp");
    hp_max=me->query_temp("hj_hp_max");

    color = HIB;
    if( hp > (hp_max * 2/10) ) color = HIR;
    if( hp > (hp_max * 4/10) ) color = HIM;
    if( hp > (hp_max * 6/10) ) color = HIY;
    if( hp > (hp_max * 8/10) ) color = HIG;
    if( hp > hp_max ) color = HIC;

    if( !temp = query("find_name") )
        temp = "���ع���";
    switch( temp )
    {
        case "��֮����": temp = HIW+temp+NOR;break;
        case "��֮����": temp = HIM+temp+NOR;break;
        case "��֮����": temp = HIC+temp+NOR;break;
        case "��֮����": temp = HIG+temp+NOR;break;
    }
    temp2 = "";
    if( me->query_temp("hj_special/xk") ) temp2 += HIW"����ա�"NOR;
    if( me->query_temp("hj_special/cm") ) temp2 += HIM"��������"NOR;
    if( me->query_temp("hj_special/ll") ) temp2 += HIC"��������"NOR;
    if( me->query_temp("hj_special/gm") ) temp2 += HIG"����â��"NOR;
    if( me->query_temp("hj_special/kz") ) temp2 += CYN"�����ơ�"NOR;
    if( me->query_temp("hj_special/sh") ) temp2 += HIB"���ػ���"NOR;
    if( me->query_temp("hj_special/rq") ) temp2 += HIR"�����项"NOR;
    if( me->query_temp("hj_special/xs") ) temp2 += HIY"��Ѱʯ��"NOR;

    if( temp2 == "" ) temp2 = " ---";

    temp3 = "";
    iii = me->query_temp("hj_game_mepower");
    while( iii >4 )
    {
        temp3 += "��";
        iii -= 5;
    }
    if( strlen( temp3 ) > 20 ) temp3 = temp3[0..19] + ">>>>";

    write( sprintf("�� %s �� LV "HIY"%d"NOR" �� ��Ϣ��%s%d"NOR"/"HIG"%d"NOR" �� �÷֣�"HIY"%d"NOR" �� ����������"HIY"%s"NOR" �� �ۼ�ɱ��NPC "HIM"%d"NOR" �� ��\n�� ���������У�%s ��\n"NOR,
        temp,me->query("huanjing2003/lv"),color,
        hp, hp_max, me->query_temp("hj_score"),temp3, me->query("huanjing2003/kill_npc"),temp2 ) );
    return 1;
}

// heal ��ʽ���£�����ʵ���Զ��ָ���
int do_gheal(string arg)
{
    object target,me=this_player();

    if( !me_ok(me) ) return 0;

    if(!me->query_temp("hj_game_skills/heal") || !me->query_temp("hj_game_damages/heal") )
        return errs("�㲢�����ûָ����ܡ�\n");

    if(!arg || arg == me->query("id") ) target=me;
    else target=present( arg,environment( me ) );
    if( !target ) return errs("��Ҫ��˭�ָ���Ϣ��\n");
    if( !target->is_character() ) return errs("�ⲻ�ǻ��\n");
    if( !living(target) ) return errs("�����ȵ�����������˵�ɡ�\n");
    if( !target->query_temp("hj_hp") || !target->query_temp("hj_hp_max") )
        return errs("����û��˿����Ϣ���������˰ɡ�\n");

    // ��ָ����ɰ�NPC�ָ���Ϣ������������NPC��Ҫ���ȥ������ :)
    // �Ѳ��ɰ���NPC�ָ���Ϣ��
    if( me->query_temp("hj_need_waiting") == "fighting" || me->query_temp("hj_fighting") )
            return errs("�㻹��ս���У�Ҫ���˵���ͣ����(halt / ht)��\n");

    if( me->query_temp("hj_healing") )
        return errs("���������ûָ�֮����\n");

    if( me->is_busy() )
        return errs("�㻹æ���ء�\n");

    if(target == me )
    {
        if( me->query_temp("hj_hp") > (me->query_temp("hj_hp_max") *9/10 ) )
            return errs("�㻹�����úܣ����ص�����Ϣ��\n");
        message_vision(CYN"$N"NOR+CYN"���������������ص����Լ�����Ϣ��\n"NOR,me);
    }
    else
    {
        if( present( "hj temp leave obj", target )      // �Ѿ���ʱ�뿪��Ϸ�ˣ����ܰ����ָ�hp
          || target->query("hj_game/npc")
          || target->query_temp("huanjing") != "start"
        )
            return errs("�㲻�ܰ�������˻ָ���Ϣ��\n");

        if(target->query_temp("hj_hp") > (target->query_temp("hj_hp_max") *9/10) )
            return errs("���˻������úܣ����ص�����Ϣ��\n");
        if( me->query_temp("hj_hp") < 100 )
            return errs("���Թ˲�Ͼ����Ϊ�������ˣ�\n");
        message_vision(CYN"$N"NOR+CYN"����������$n"NOR+CYN"�ı��ϣ����𡸻ָ�֮��������\n"NOR, me, target );
    }

    me->set_temp("hj_healing", target);
    me->set_temp("hj_need_waiting", "healing");

    remove_call_out("healing");
    call_out("healing", 1, me );
    return 1;
}

void healing( object me)
{
    object env_me,env_target, target;
    int heal_lv, heal_hp;

    if( !me || !me_ok(me) )
        return;
    if( !me->query_temp("hj_need_waiting")
      || me->query_temp("hj_need_waiting") != "healing"
    )
        return;
    target = me->query_temp( "hj_healing" );
    if( !target
      || !target->query_temp("huanjing")
      || target->query_temp("huanjing") != "start"
      || !target->query_temp("hj_hp")
      || target->query_temp("hj_hp") <1
      || !target->query_temp("hj_hp_max")
      || present( "hj temp leave obj", target )
    )
         return hj_halt( CYN"$N"NOR+CYN"�ھ�һ����ֹͣ�����ûָ�֮����\n"NOR );
    env_target = environment( target );
    env_me = environment( me );
    if( !env_target || env_target != env_me || !env_target->query("room_mark") 
     || env_target->query("room_mark") == 1 )
        return hj_halt( CYN"$N"NOR+CYN"�ھ�һ����ֹͣ�����ûָ�֮����\n"NOR );
    // �����ж�ͨ����
    if( target->query_temp("hj_hp") > (target->query_temp("hj_hp_max") *9/10) )
    {
        if( me == target )
            return hj_halt( CYN"$N"NOR+CYN"��Ϣ��˳������������һ������\n"NOR);
        return hj_halt( CYN"$N"NOR+CYN"����$n"NOR+CYN"�Ѿ���Ϣ˳����������������\n"NOR);
    }

    if( me->is_busy() )
    {
        remove_call_out("healing");
        call_out("healing", 1, me );
        return;
    }
    heal_lv = me->query_temp("hj_game_damages/heal");
    heal_hp = (heal_lv / 2 + random(heal_lv / 2 ));  // lv 100 = 50 + random(50)
    // ��֮������������Ч��  ʹ�ûָ�֮����ʱЧ����ǿ
    if( me->query_temp( "hj_game_find" ) == "yu" )
        heal_hp += (heal_hp / 3) + random(heal_hp/5);
    if(target == me)
    {

        // �ɻ�֮��Ψһ����(1)��ʹ�� heal ʱ����æʱ
        if( me->query_temp("hj_special/rq") )
            me->start_busy(1)+random(2);
        else me->start_busy(2+random(2));

        me->add_temp("hj_hp", heal_hp );
        if(me->query_temp("hj_hp") > me->query_temp("hj_hp_max") )
            me->set_temp("hj_hp", me->query_temp("hj_hp_max") );
        message_vision(CYN"$N"NOR+CYN"���ĵ�����Ϣ��ֻ�������ƻָ���Щ��\n"NOR,me);
        tell_object( me, sprintf("��ǰ�� %d / %d \n",
            me->query_temp("hj_hp"), me->query_temp("hj_hp_max") ) );

        /* ȡ��
        // ����������ܣ���������ʧһ������
        if( !random(me->query_temp("hj_game_mepower") * 3 )
          && me->query_temp("hj_game_mepower") > 20 )
        {
            me->add_temp("hj_game_mepower",-1);
            tell_object(me,HIY"��ֻ����Ԫ���ָ�����࣬������ȴ�ƺ�С�ˡ�\n"NOR);
        }
        */
        // ��Ҳ���ܻ�õȼ�����
        if( !random( me->query_temp("hj_game_damages/heal") * 2 ) )
        {
            me->add_temp("hj_game_damages/heal",1);
            if(me->query_temp("hj_game_damages/heal") > 99)
                me->set_temp("hj_game_damages/heal",99);
            else tell_object(me,HIY"��ԡ��ָ�֮����������ֽ���һ�㣡\n"NOR);
        }
        remove_call_out("healing");
        call_out("healing", 1, me );
        return;
    }

    if( me->query_temp("hj_hp") < 100 )
        return hj_halt( CYN"$N"NOR+CYN"���ڰ���$n"NOR+CYN"���ˣ�ȴ�����Լ���Ϣ������ֻ�ð��֡�\n"NOR);


    // �ɻ�֮��Ψһ����(2)��ʹ�� heal ʱ����æʱ
    if( me->query_temp("hj_special/rq") )
        me->start_busy( 1+random(3) );
    else
        me->start_busy(3+random(3));
    // ȡ��������
    // ����Ϊ��NPC�������ң����ˣ��Է�����æʱ��
    //    if( !target->query("hj_game/npc") )
    //        target->start_busy(2+random(2));
    target->add_temp("hj_hp", heal_hp );

    if(target->query_temp("hj_hp") > target->query_temp("hj_hp_max") )
        target->set_temp("hj_hp", target->query_temp("hj_hp_max") );

    message_vision(CYN"$N"NOR+CYN"ȫ��ʩ��Ϊ$n"NOR+CYN"���ˣ�ֻ����$n"NOR+CYN"����ɫ��ת����ࡣ\n"NOR, me, target);
    // ��������(�����Ƿ�NPC)�������һС��ļӷ֣�����Ҫ�����������Ϣ��
    // �Ѹ��ģ���Ҫ�����Լ���Ϣ��С�������������е÷֡�
    me->add_temp("hj_hp",-random( heal_lv /3 ) );
    message_vision(CYN"$N"NOR+CYN"�۾�����ת�ۼ��������ֳ�ƣ��֮ɫ��\n"NOR,me);
    remove_call_out("healing");
    call_out("healing", 1, me );
    return;
}

int do_hjquit(string arg)
{
    object qxd,me = this_player();

    if( !me_ok(me) ) return errs("�㲻��ʹ�ñ�ָ�\n");

    if ( !arg || (arg!= "fail" && arg!="ok") )
        return errs(HIG"\n             <hjquit> ָ��ʹ����ʾ��

< hjquit fail >     �������еĳɼ��������˳� �þ� ��Ϸ��
                      "HIR"ʹ�ô�ָ��������1�㹱�׶ȣ������á�"NOR"
< hjquit ok >       ��������ʽ�˳�������ʹ�� �ع�֮������
                      ��������� 500 �����ϵĵ�ǰ�÷֣�����
                      ��Ҫһ���� �ѽ�����Ϸ ʱ�䡣
\n"NOR);

    if ( arg == "fail" )
    {
        if( me->query("shenzhou/pts") < 1 )
            return errs("����1�㹱�׶ȶ�û�У�����ʹ�ñ�ָ�\n");
        write("��������ǿ���˳�ָ�����ʧ�ܵ�����˳� �þ� 1 ��Ϸ��"HIR"��ָ��۳���һ�㹱�׶ȣ�\n"NOR);
        me->add("shenzhou/pts", -1);
        me->set_temp("hj_hp",-1);
        me->start_busy(5);
        return 1;
    }

    if( me->is_busy() || me->query_temp("hj_need_waiting") )
        return errs("�㻹æ���ء�\n");

    qxd = present( "qixing deng",me);
    if(!qxd || qxd->query("my_master") != me )
        return errs("������û�����ǵƣ����������㲻���������ˣ�����\n");

    if( !qxd ->query("can_quit_hj") )
        return errs("��Ÿս�����Ϸû��ã�ȷʵҪ�˳���ʹ�� <hjquit fail> ָ���������˳���\n"HIR"��ע�⣬ʹ�� fail ����ָ���˳�����ۼ���Ĺ��׶�1�㣬�����ã�\n"NOR);

    if( !me->query_temp("hj_score") || me->query_temp("hj_score") < 500 )
        return errs("�㵱ǰ����Ϸ�÷ֲ��� 500 �֣�ȷʵҪ�˳���ʹ�� <hjquit fail> ָ���������˳���\n"HIR"��ע�⣬ʹ�� fail ����ָ���˳�����ۼ���Ĺ��׶�1�㣬�����ã�\n"NOR);

    if( qxd ->query("wait_over") == "yes" )
        return errs("�����Ϸʱ�伴������������Ϊ�ȴ����ɡ�\n");

    message_vision(CYN"$N"NOR+CYN"�����е�������ʵӳ�֣���\n"NOR,me);
    write(HIR"ʹ�ñ�ָ����۳���� 500 ����Ϸ�÷֣�\n"NOR);
    me->add_temp("hj_score" , - 499);
    me->start_busy(3);

    qxd->set("use_huigui","yes");

    message_vision(WHT"ֻ��һ�����֪�Ӻδ�Ʈ����������Ũ����\n"NOR,me);
    return 1;
}

int do_hjtime()
{
    object me = this_player();
    int enter_time = me->query_temp("hj_enter_time");;

    write(sprintf( "�������Ϸ��ʱ���� %s �����ڵ�ʱ���� %s ��\n��Ϸʱ��%s ��\n",
        !enter_time ? "δ֪" : ctime_format( enter_time ),  ctime_format(),
        !enter_time ? "δ֪" : sprintf( "�� %d Сʱ %d �� %d ��", 
            ( time() - enter_time ) / 3600,
            ( ( time() - enter_time ) % 3600 ) / 60,
            ( ( time() - enter_time ) % 3600 ) % 60 ) ) );

    return 1;
}

int do_halt()
{
    object me = this_player(),target;
    string temp;

    if( !me_ok(me) )
        return errs( "ʲô��\n");
    if( ( !me->query_temp("hj_healing") && !me->query_temp("hj_fighting")) ||
        !me->query_temp("hj_need_waiting") )
    {
        me->delete_temp( "hj_need_waiting" );
        return errs( "�����ڲ�����ս���������С�\n");
    }
    temp = me->query_temp("hj_need_waiting");
    if( temp == "healing" )
    {
        target = me->query_temp("hj_healing");
        if( target == me )
        {
            hj_halt(CYN"$N"NOR+CYN"����һ�ڴ�����ֹͣ�˵�����Ϣ��\n"NOR);
            return 1;
        }
        hj_halt(CYN"$N"NOR+CYN"����һ�գ�ͣ���˶�$n"NOR+CYN"�����ˡ�\n"NOR);
        return 1;
    }
    hj_halt(CYN"$N"NOR+CYN"���һ�У�Ծ��սȦ�����ˡ�\n"NOR);
    return 1;
}

// �����ˣ���ң����ڣ�������ᱻ��������Բ��ÿ���
// ��ʱ�з��������⡣
void delete_special_sks( object me, string sks, string sks_name )
{
    // ����ô˵��������ȫ��Ҫ����
    if( !me || !me_ok(me) )
        return;
    // ����� wiztools ֹͣ�����ã�������ͣһ�Σ���Ǹ�Ц������Ҫ�������Ƿ����á�
    if( !me->query_temp("hj_special/"+sks) )
        return;
    me->delete_temp("hj_special/"+ sks);
    message_vision( HIY"\nֻ��Χ��$N"HIY"��һȦ΢�����ˣ���"+sks_name+"�����ܵ�Ч����ʧ�ˡ�\n\n"NOR, me);
}

int do_gyun( string arg )
{
    // ���ָ�����չ���ã������ˣ��������ա�
    // ʵ����Ҫ����ʱ���ٸ�Ϊ������ķ�ʽ��
    object me = this_player();
    string *sp_sks = ({ "xk", "cm", "ll", "gm", "kz", "sh", "rq", "xs" }), find_name;
    int HpNeed = 50, hpneed, del_time;
    // HpNeed ���ܸ������� 20%
    mapping sks_sks = ([
        "xk": ({ "���", "��֮����", "hfzj", "����֮��" }), 
        "cm": ({ "����", "��֮����", "hyzj", "����֮��" }),
        "ll": ({ "����", "��֮����", "llzj", "����֮��" }),
        "gm": ({ "��â", "��֮����", "ydzj", "����֮��" }),
        "kz": ({ "����",       "--", "heal", "�ָ�֮��" }),
        "sh": ({ "�ػ�",       "--", "dhzj", "���֮��" }),
        "rq": ({ "����",       "--", "fhzj", "�ɻ�֮��" }),
        "xs": ({ "Ѱʯ",       "--", "gszj", "��ʯ֮��" }),
    ]);


    if( !me_ok(me) )
    {
        write("ʲô��\n");
        return 1;
    }

    if( !arg || member_array( arg, sp_sks ) == -1 )
    {
        write( sprintf("
      ������⼼�����������
"WHT"=====================================
"HIW"    ���(xk)   >>>>>>   %s
"HIM"    ����(cm)   >>>>>>   %s
"HIC"    ����(ll)   >>>>>>   %s
"HIG"    ��â(gm)   >>>>>>   %s
"NOR+CYN"    ����(kz)   >>>>>>   %s
"HIB"    �ػ�(sh)   >>>>>>   %s
"HIR"    ����(rq)   >>>>>>   %s
"HIY"    Ѱʯ(xs)   >>>>>>   %s
"NOR+WHT"=====================================\n"NOR, 
    me->query_temp("hj_special/xk") ? "������" : "--",
    me->query_temp("hj_special/cm") ? "������" : "--",
    me->query_temp("hj_special/ll") ? "������" : "--",
    me->query_temp("hj_special/gm") ? "������" : "--",
    me->query_temp("hj_special/kz") ? "������" : "--",
    me->query_temp("hj_special/sh") ? "������" : "--",
    me->query_temp("hj_special/rq") ? "������" : "--",
    me->query_temp("hj_special/xs") ? "������" : "--") );
        return 1;
    }

    // æʱ�����е���������Ϊ�˿�����ս���л����������ü���
    if( me->query_busy() > 5 )
    {
        write("������ʵ����̫æ��(æʱ5������)���޷������������⼼�ܡ�\n");
        return 1;
    }
    // �����ظ����á�
    if( me->query_temp("hj_special/"+ arg) )
    {
        write("����������������ܡ�\n");
        return 1;
    }
    // ��Ҫ������Ϣ
    hpneed = HpNeed + random(HpNeed/5);
    if( me->query_temp("hj_hp") < (hpneed + 50) )
    {
        write("�����Ϣ̫�����޷��������⼼�ܡ�\n");
        return 1;
    }
    if( me->query_temp("hj_game_damages/"+ sks_sks[arg][2] ) < YUN_LvNeed )
    {
        write(sprintf("��ġ�%s���ȼ��������޷����á�%s�����ܡ�\n",
            sks_sks[arg][3], sks_sks[arg][0] ) );
        return 1;
    }
    // Ч��
    del_time = me->query_temp("hj_game_damages/" + sks_sks[arg][2] ) * 4 / 5;
    // ����F,Y,L,D�������⼼���Ǳ�������Ч������
    if( sks_sks[arg][1] != "--" && query("find_name") != sks_sks[arg][1] )
        del_time /= 2;

    me->set_temp("hj_special/"+arg, del_time );
    // ��� set ��ֵ��ʵ�����壬��ʹ���������ֵ��
    me->add_temp("hj_hp", -hpneed);
    //    me->start_busy( me->query_busy() + 1 );
    // ȡ���������õ�æʱ�����䱾����Ҫ������Ϣ���ʲ�������æʱ��
    // �����⼼����ʱ������
    switch( sks_sks[arg][0] )
    {
        // #########################################################
        case "���":
            message_vision(HIW"\nֻ��$N"HIW"�ſ�˫�֣������Ŀ�������ģ���ʱ��ƽ����磬$N"HIW"���������գ�\n"
                "�����Ƿ�֮����ա��ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "����":
            message_vision(HIM"\nֻ��$N"NOR+HIM"���ֻ��գ���ͷ��ĿĬ�����ģ���ʱ����������з�ӿ������\n"
                "��������֮���������ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "����":
            message_vision(HIC"\nֻ��$N"HIC"˫ĿԲ����ȭ���죬���д��һ������ʱȫ������ž���죬���ƾ��ˣ�\n"
                "��������֮���������ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "��â":
            message_vision(HIG"\nֻ��$N"HIG"����̯�ƻ���ǰ�죬ɲ�Ǽ���������һ��ҫ�۹�â��˲������ȫ��\n"
                "�����ǵ�֮����â���ؼ���\n\n"NOR, me);
            break;
        // #########################################################
        case "����":
            message_vision( CYN"\nֻ��$N"NOR+CYN"˫�ƺ�ʮ��ĬĬ�����˼������ģ���ʱһ��������������ľ�ƽ�ͣ����޷��ǡ�\n"
                "�����ǻָ�֮�������ơ��ؼ���\n\n"NOR, me );
            del_time *= 4;  // Ч���־�
            break;
        // #########################################################
        case "�ػ�":
            message_vision( HIB"\nֻ��$N"HIB"˫��ʳָ���ö��ģ��������ģ��Ĵ���ʱ����һ������֮�����������廤��һ�㣡\n"
                "�����Ƕ��֮�����ػ����ؼ���\n\n"NOR, me );
            break;
        // #########################################################
        case "����":
            message_vision( HIR"\nֻ��$N"HIR"������ȭ��������֮�ԣ��������ʳ���ж�ָ������Ц�ݣ���һ������Ү����\n"
                "�����Ƿɻ�֮�������项�ؼ���\n\n"NOR,me);
            break;
        // #########################################################
        case "Ѱʯ":
            message_vision( HIY"\nֻ��$N"HIY"˫�ֽ��շ�����ǰ����Ŀ����������ʯͷ��ʯͷ����Ҫʯͷ������\n"
                "�����ǹ�ʯ֮����Ѱʯ���ؼ���\n\n"NOR,me);
            break;
        // #########################################################
    }
    call_out( "delete_special_sks", del_time , me, arg, sks_sks[arg][0] );
    write( sprintf( "����Լ���� %d ��þ�ʱ����Ч��\n", del_time ) );
    return 1;
}
