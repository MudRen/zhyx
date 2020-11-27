// message.c
// Update by Doing
// Update by Lonely At 08/11/2002

#include <ansi.h>
string sort_msg(string input)
{
#ifdef DOING_IMPROVED
        return efun::sort_string(input, 60, 0);
#else
        int i;
        int sl;
        int len;
        int esc;
        string result;
        result = "";

        len = 0;
        esc = 0;
        sl = strlen(input);
        for (i = 0; i < sl; i++)
        {
                if (len >= 64 && input[i] != '\n')
                {
                        switch (input[i..i+1])
                        {
                        case "��":
                        case "��":
                        case "��":
                        case "��":
                        case "��":
                        case "��":
                        case "��":
                        case " )":
                        case "��":
                        case "��":
                                break;
                        default:
                                len = 0;
                                result += "\n";
                                break;
                        }
                }

                if (input[i] == 27)
                        esc = 1;

                if (! esc)
                {
                        if (input[i] > 160)
                        {
                                result += input[i..i+1];
                                i ++;
                                len += 2;
                                continue;
                        }
                        if (input[i] == '\n')
                        {
                                result += "\n";
                                len = 0;
                                continue;
                        }
                }

                result += input[i..i];
                if (! esc) len++;

                if (esc && input[i] == 'm')
                        esc = 0;
        }

        if (i < sl)
                result += input[i..sl-1];

        return result;
#endif
}

varargs void message_vision(string msg, object me, object you)
{
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3;

	my_name = me->name();
	my_gender = me->query("gender");

	str1 = replace_string(msg,  "$P", gender_self(my_gender));
	str1 = replace_string(str1, "$N", gender_self(my_gender));
	str3 = replace_string(msg,  "$P", my_name);
	str3 = replace_string(str3, "$N", my_name);

	if (you)
        {
	        your_name = you->name();
	        your_gender = you->query("gender");
	        str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
	        str1 = replace_string(str1, "$n", your_name);

		str3 = replace_string(str3, "$p", your_name);
		str3 = replace_string(str3, "$n", your_name);

		str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
		str2 = replace_string(str2, "$p", gender_self(your_gender));
		str2 = replace_string(str2, "$N", my_name);
		str2 = replace_string(str2, "$n", gender_self(your_gender));
		message("vision", str2, you);
        }

        message("vision", str1, me);
        message("vision", str3, all_inventory(environment(me)), ({ me, you }));
        if (environment(me)->query("fight_room"))
                environment(me)->relay_message(str3);
}

varargs void message_sort(string msg, object me, object you)
{
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3;

	my_name= me->name();
	my_gender = me->query("gender");
	str1 = replace_string(msg,  "$P", gender_self(my_gender));
	str1 = replace_string(str1, "$N", gender_self(my_gender));
	str3 = replace_string(msg,  "$P", my_name);
	str3 = replace_string(str3, "$N", my_name);
	if( you ){
		your_name= you->name();
		your_gender= you->query("gender");
		str2 = replace_string(msg,  "$P", gender_pronoun(my_gender));
		str2 = replace_string(str2, "$p", gender_self(your_gender));
		str2 = replace_string(str2, "$N", my_name);
		str2 = replace_string(str2, "$n", gender_self(your_gender));
		message("vision", sort_msg(str2), you);
		str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
		str1 = replace_string(str1, "$n", your_name);
		str3 = replace_string(str3, "$p", your_name);
		str3 = replace_string(str3, "$n", your_name);
	}
	message("vision", sort_msg(str1), me);
	message("vision", sort_msg(str3),  environment(me), ({ me, you}) );
}

/* Definition of the level of showing combat message */
#define	SHOW_ALL		0
#define	SHOW_DAMAGE		1
#define	SHOW_BRIEF_DAMAGE	2
#define	SHOW_BRIEF_SELF_DAMAGE	3
#define	SHOW_NONE		4

varargs void message_combatd(string msg, object me, object you, string damage_info)
{
	string my_gender, your_gender, my_name, your_name;
	string str1, str2, str3f, str3d;
	mixed my_flag;
	mixed your_flag;
	int damage_flag;
	int brief;
        int others;
        object ob;
        object *obs;

	brief = 1;
        if (! stringp(damage_info))
	{
		// No damage_info defined, so I must show full message.
		damage_info = "";
		brief = 0;
                msg = "\n" + msg;
	}

        damage_flag = (strlen(damage_info) > 0);

	my_name= me->name();
	my_gender = me->query("gender");

	if (you)
        {
		your_name = you->name();
		your_gender = you->query("gender");
        }

        if (userp(me))
        {
        	if (! brief) my_flag = SHOW_ALL;
                else
        	{
        		my_flag = me->query("env/combatd");
        		if (stringp(my_flag) && my_flag == "YES") my_flag = SHOW_BRIEF_DAMAGE;
        		if (! intp(my_flag)) my_flag = SHOW_ALL;
        	}

        	if (my_flag >= SHOW_BRIEF_SELF_DAMAGE || my_flag && ! damage_flag)
        	{
        		if (! stringp(str1 = me->query("env/ignore_combat")))
        			str1 = "";
        		else
        			str1 += "\n";
        	} else
        	if (my_flag == SHOW_BRIEF_DAMAGE)
                        str1 = (string)damage_info;
        	else
                        str1 = msg + (string)damage_info;

	        str1 = replace_string(str1, "$P", gender_self(my_gender));
	        str1 = replace_string(str1, "$N", gender_self(my_gender));
                if (you)
                {
        	        str1 = replace_string(str1, "$p", gender_pronoun(your_gender));
        	        str1 = replace_string(str1, "$n", your_name);
                }

        	if (strlen(str1) > 0)
                        message("tell_object", str1, me);
        }

	if (you && userp(you))
        {
		if (! brief) your_flag = SHOW_ALL;
		else
                {
		        your_flag = you->query("env/combatd");
		        if (stringp(your_flag) && your_flag == "YES") your_flag = SHOW_BRIEF_DAMAGE;
		        if (! intp(your_flag)) your_flag = SHOW_ALL;
                }

		if (your_flag == SHOW_ALL || damage_flag && your_flag < SHOW_NONE)
                {
			if (your_flag <= SHOW_DAMAGE)
                                str2 = msg + (string)damage_info;
			else
                                str2 = (string)damage_info;

                        str2 = replace_string(str2, "$P", gender_pronoun(my_gender));
		        str2 = replace_string(str2, "$p", gender_self(your_gender));
		        str2 = replace_string(str2, "$N", my_name);
		        str2 = replace_string(str2, "$n", gender_self(your_gender));
                        if (strlen(str2) > 0)
		                message("tell_object", str2, you);
                }
	}

        if (environment(me)->query("fight_room"))
        {
                str3f = msg;
                str3d = (string)damage_info;
                str3f = replace_string(str3f, "$P", my_name);
                str3f = replace_string(str3f, "$N", my_name);
                str3d = replace_string(str3d, "$P", my_name);
                str3d = replace_string(str3d, "$N", my_name);
                if (you)
                {
                        str3f = replace_string(str3f, "$p", your_name);
                        str3f = replace_string(str3f, "$n", your_name);
                        str3d = replace_string(str3d, "$p", your_name);
                        str3d = replace_string(str3d, "$n", your_name);
                }
                str3f += str3d;
                environment(me)->relay_message(str3f);
        }

        obs = filter_array(all_inventory(environment(me)),
                           (: userp($1) || $1->want_receive_msg() :)) -
              ({ me, you });
        others = sizeof(obs);
        if (others)
        {
                str3f = msg;
                str3d = (string)damage_info;
        	str3f = replace_string(str3f, "$P", my_name);
        	str3f = replace_string(str3f, "$N", my_name);
        	str3d = replace_string(str3d, "$P", my_name);
        	str3d = replace_string(str3d, "$N", my_name);
                if (you)
                {
        		str3f = replace_string(str3f, "$p", your_name);
        		str3f = replace_string(str3f, "$n", your_name);
        		str3d = replace_string(str3d, "$p", your_name);
        		str3d = replace_string(str3d, "$n", your_name);
                }

                if (brief)
                        str3f += str3d;
                else
                        // no damage info, so I must show all the message info
                        str3d = str3f;

                if (strlen(str3f) < 1)
                        return;

                foreach (ob in obs)
                {
                        switch (ob->query("env/combatd"))
                        {
                        case SHOW_NONE:
                                break;

                        case SHOW_BRIEF_DAMAGE:
                        case SHOW_BRIEF_SELF_DAMAGE:
                                message("tell_object", str3d, ob);
                                break;

                        default:
                                message("tell_object", str3f, ob);
                                break;
                        }
                }
        }
}

void tell_object(object ob, string str)
{
	message("tell_object", str, ob);
}

varargs void tell_room(mixed ob, string str, object *exclude)
{
	if (ob) message("tell_room", str, ob, exclude);
}

void shout(string str)
{
	message("shout", str, users(), this_player());
}

void write(string str)
{
	if (this_player())
		message("write", str, this_player());
	else if (previous_object())
		message("write", str, previous_object());
	else
		efun::write(str);
}

varargs void say(string str, mixed exclude)
{
	if (living(previous_object()))
                message("say", str, environment(previous_object()), previous_object());
	else if (this_player())
		message("say", str, environment(this_player()), this_player());
}


/*
varargs string replace_color(string arg,int flag)
{
        arg = replace_string(arg, "$BLK$", flag?BLK:"");
        arg = replace_string(arg, "$RED$", flag?RED:"");
        arg = replace_string(arg, "$GRN$", flag?GRN:"");
        arg = replace_string(arg, "$YEL$", flag?YEL:"");
        arg = replace_string(arg, "$BLU$", flag?BLU:"");
        arg = replace_string(arg, "$MAG$", flag?MAG:"");
        arg = replace_string(arg, "$CYN$", flag?CYN:"");
        arg = replace_string(arg, "$WHT$", flag?WHT:"");
        arg = replace_string(arg, "$HIR$", flag?HIR:"");
        arg = replace_string(arg, "$HIG$", flag?HIG:"");
        arg = replace_string(arg, "$HIY$", flag?HIY:"");
        arg = replace_string(arg, "$HIB$", flag?HIB:"");
        arg = replace_string(arg, "$HIM$", flag?HIM:"");
        arg = replace_string(arg, "$HIC$", flag?HIC:"");
        arg = replace_string(arg, "$HIW$", flag?HIW:"");
        arg = replace_string(arg, "$NOR$", flag?NOR:"");
        arg = replace_string(arg, "$BLINK$", flag?BLINK:"");
        
        // Background color
        arg = replace_string(arg, "$BBLK$", BBLK);
        arg = replace_string(arg, "$BRED$", BRED);
        arg = replace_string(arg, "$BGRN$", BGRN);
        arg = replace_string(arg, "$BYEL$", BYEL);
        arg = replace_string(arg, "$BBLU$", BBLU);
        arg = replace_string(arg, "$BMAG$", BMAG);
        arg = replace_string(arg, "$BCYN$", BCYN);
        arg = replace_string(arg, "$HBRED$", HBRED);
        arg = replace_string(arg, "$HBGRN$", HBGRN);
        arg = replace_string(arg, "$HBYEL$", HBYEL);
        arg = replace_string(arg, "$HBBLU$", HBBLU);
        arg = replace_string(arg, "$HBMAG$", HBMAG);
        arg = replace_string(arg, "$HBCYN$", HBCYN);
        if(flag) arg+=NOR;
        return arg;
}

string clean_color(string arg)
{
        arg = replace_string(arg, BLK, "");
        arg = replace_string(arg, RED, "");
        arg = replace_string(arg, GRN, "");
        arg = replace_string(arg, YEL, "");
        arg = replace_string(arg, BLU, "");
        arg = replace_string(arg, MAG, "");
        arg = replace_string(arg, CYN, "");
        arg = replace_string(arg, WHT, "");
        arg = replace_string(arg, HIR, "");
        arg = replace_string(arg, HIG, "");
        arg = replace_string(arg, HIY, "");
        arg = replace_string(arg, HIB, "");
        arg = replace_string(arg, HIM, "");
        arg = replace_string(arg, HIC, "");
        arg = replace_string(arg, HIW, "");
        arg = replace_string(arg, NOR, "");
        arg = replace_string(arg, BLINK, "");
        // BackGround Color
        arg = replace_string(arg, "$BBLK$", "");
        arg = replace_string(arg, "$BRED$", "");
        arg = replace_string(arg, "$BGRN$", "");
        arg = replace_string(arg, "$BYEL$", "");
        arg = replace_string(arg, "$BBLU$", "");
        arg = replace_string(arg, "$BMAG$", "");
        arg = replace_string(arg, "$BCYN$", "");
        arg = replace_string(arg, "$HBRED$", "");
        arg = replace_string(arg, "$HBGRN$", "");
        arg = replace_string(arg, "$HBYEL$", "");
        arg = replace_string(arg, "$HBBLU$", "");
        arg = replace_string(arg, "$HBMAG$", "");
        arg = replace_string(arg, "$HBCYN$", "");
        return arg;
}
*/


void message(mixed arg, string message, mixed target, mixed exclude)
{
        efun::message(arg, message, target, exclude);
}

void message_system(string message)
{
	message("system", HIW "\n��ϵͳ��ʾ��" + message + "\n" NOR,
                all_interactive(), 0);
}

int notify_fail(string msg)
{
        if (this_player()) 
        {

/*
        	if (this_player()->query_temp("big5")) 
        		msg = (string)LANGUAGE_D->GB2Big5(msg); 
*/
	        this_player()->set_temp("notify_fail", msg);
                return efun::notify_fail(ESC "[256D" ESC "[K" + msg);
        } else
                return 0;
}

string query_fail_msg()
{
        return this_player()->query_temp("notify_fail");
}

/*
string read_file(string file)
{
        object user = this_object();

        if (objectp(user) && userp(user) && wizardp(user) && find_object(SECURITY_D) 
        &&  ! SECURITY_D->valid_read(file, user, "read_file"))
        {        
                log_file("file/try_read_file", sprintf("%s %s(%s) try read %s.\n", 
                         ctime(time()), geteuid(user), wizhood(user), file));
	        return "Permission denied��\n";
	}        

        return efun::read_file(file);
}
*/

