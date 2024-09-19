/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stevennkeneng <snkeneng@student.42ber      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:43:25 by stevennke         #+#    #+#             */
/*   Updated: 2024/09/19 17:44:37 by stevennke        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	enqueue(t_queue *queue, t_point point)
{
	t_queue_node	*new_node;

	new_node = malloc(sizeof(t_queue_node));
	new_node->point = point;
	new_node->next = NULL;
	if (queue->rear == NULL)
	{
		queue->front = new_node;
		queue->rear = new_node;
	}
	else
	{
		queue->rear->next = new_node;
		queue->rear = new_node;
	}
}

int	is_queue_empty(t_queue *queue)
{
	return (queue->front == NULL);
}

t_point	dequeue(t_queue *queue)
{
	t_queue_node	*temp;
	t_point			point;

	temp = queue->front;
	point = temp->point;
	queue->front = queue->front->next;
	if (queue->front == NULL)
		queue->rear = NULL;
	free(temp);
	return (point);
}
