#include "Player.h"

Player::Player(Tank_hull* t, float rop, float m_pi, float ang, float msf, float msb, float maf, float mab, float mmsf)
{
	this->t = t;
	rotation_speed = t->get_traverse_speed();
	
	 m_pi = 3.14159265358979323846;
	 ang = 60 * M_PI / 2;
	msf = momentary_speed_forward;
	msb = momentary_speed_backward;
	maf = momentary_acceleration_forward;
	mab = momentary_acceleration_backward;
	mmsf = momentary_max_speed_forward;
	rop = rotation;
	//std::string tank_name;

	


	//player_sprite_hull.setTexture(Tank_hull);
}

Player::~Player(void)
{

}


void Player::update()
{
	//t->get_sprite().move(0.5, 0);


	
	//----------------Key_Pressing_check--------------------------------------//
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{


		momentary_acceleration_forward = tank_hull.get_acceleration_forward();
		momentary_max_speed_forward = tank_hull.get_max_speed_forward();
		momentary_speed_forward += _elapsed * momentary_acceleration_forward;

		if (momentary_speed_forward > momentary_max_speed_forward)
		{
			momentary_speed_forward = momentary_max_speed_forward;
		}


		// Voi heittää helvettiin.
		momentary_speed_forward = 5.0f;

		//float x = sin(t->get_sprite().getRotation()*3.14159265*momentary_speed_forward);
		//float y = cos(t->get_sprite().getRotation()*3.14159265)*momentary_speed_forward;
		//set_position(x, y);
		
		//t->get_sprite().move(sin(t->get_sprite().getRotation()*3.14159265*momentary_speed_forward), cos(t->get_sprite().getRotation()*3.14159265)*momentary_speed_forward);
		//t->get_sprite().setPosition(t->get_sprite().getPosition().x + x, t->get_sprite().getPosition().y + y);

		//t->set_position(t->get_position().x + x, t->get_position().y + y);
		
	}

		
		

		//tank_hull

		/*
		hull_movement_speed_forwards += _elapsed * hull_movement_acceleration;


		if (hull_movement_speed_forwards > hull_movement_speed_forwards_max)
		{
		hull_movement_speed_forwards = hull_movement_speed_forwards_max;
		}


		//Tank hull moves now to the direction it faces.
		sprite_tank_hull.move(sin(sprite_tank_hull.getRotation()*3.14159265 / 180) * hull_movement_speed_forwards, cos(sprite_tank_hull.getRotation()*3.14159265 / 180)*-hull_movement_speed_forwards);
		sprite_tank_turret.setPosition(sprite_tank_hull.getPosition());
		view.setCenter(sprite_tank_hull.getPosition());

		//	//----------------Tank_rotation_and_movement-----------------------------------------------------//
		//	float rot_turret = 0;
		//	float rot_hull = 0;
		//	float turret_rot_speed = 1.2;
		//	float hull_rot_speed = 0.8;
		//
		//	float o_clock = 1 / 60;
		//
		//	float hull_movement_acceleration = 0.2;
		//	float hull_movement_speed_forwards = 0;
		//	float hull_movement_speed_forwards_max = 2.1;
		//
		//	float hull_movement_speed_backwards = 0;
		//	float hull_movement_speed_backwards_max = 0.7;
		//
		//	float speed = 5;
		//	float angle = 60 * M_PI / 2;
		//
		//	float move_x = speed * cos(angle);
		//	float move_y = speed * sin(angle);
		//
		//
		//
		//	//-----------------------------------------------------------------------------------------------//
		//

		*/
					

	

	//on_draw();

}

void Player::set_position(float x, float y)
{
	this->x = x;
	this->y = y;

	t->set_position(this ->x, this->y);
	
}

float Player::rotate(float rotation_speed)
{
	return 0;//t->set_rotation(rotation_speed);

}

sf::Vector2f Player::get_position()
{
	return	t->get_position();
}

void Player::on_draw(sf::RenderWindow* win)
{
	t->on_draw(win);
}

void Player::set_rotation(float rot)
{

	rotation = rot;

}