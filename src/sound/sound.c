/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:57:05 by hstein            #+#    #+#             */
/*   Updated: 2024/06/03 14:19:38 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube.h"

//Enviroment FUN-Functions
int	init_sounds_1(t_sound *sound)
{
	sound->result = ma_engine_init(NULL, &sound->engine);
	sound->result = ma_sound_init_from_file(&sound->engine, \
		"./sound/motor.mp3", 0, NULL, NULL, &sound->motor);
	sound->result = ma_sound_init_from_file(&sound->engine, \
		"./sound/crash.mp3", 0, NULL, NULL, &sound->crash);
	sound->result = ma_sound_init_from_file(&sound->engine, \
		"./sound/siren.mp3", 0, NULL, NULL, &sound->siren);
	sound->result = ma_sound_init_from_file(&sound->engine, \
		"./sound/Tokyo_Drift_8bit.mp3", 0, NULL, NULL, &sound->soundtrack);
	return (0);
}

void	setup_sounds(t_data *data)
{
	init_sounds_1(&data->sound);
	ma_sound_set_volume(&data->sound.motor, 0.8);
	ma_sound_set_volume(&data->sound.crash, 1);
	ma_sound_set_volume(&data->sound.siren, 1);
	ma_sound_set_volume(&data->sound.soundtrack, 1);
	ma_sound_set_pitch(&data->sound.motor, 0.2);
	ma_sound_set_looping(&data->sound.motor, 1);
	ma_sound_set_looping(&data->sound.siren, 1);
	ma_sound_set_looping(&data->sound.soundtrack, 1);
	ma_sound_start(&data->sound.motor);
	ma_sound_start(&data->sound.soundtrack);
}

void	terminate_sounds(t_data *data)
{
	ma_sound_stop(&data->sound.motor);
	ma_sound_stop(&data->sound.siren);
	ma_engine_uninit(&data->sound.engine);
}
