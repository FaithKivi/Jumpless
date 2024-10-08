/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-19     Shell        Fixup UP irq spinlock
 */
#include <rthw.h>
#include <rtthread.h>

/**
 * @brief   Initialize a static spinlock object.
 *
 * @param   lock is a pointer to the spinlock to initialize.
 */
void rt_spin_lock_init(struct rt_spinlock *lock)
{
    RT_UNUSED(lock);
}

/**
 * @brief   This function will lock the spinlock, will lock the thread scheduler.
 *
 * @note    If the spinlock is locked, the current CPU will keep polling the spinlock state
 *          until the spinlock is unlocked.
 *
 * @param   lock is a pointer to the spinlock.
 */
void rt_spin_lock(struct rt_spinlock *lock)
{
    rt_enter_critical();
    RT_SPIN_LOCK_DEBUG(lock);
}

/**
 * @brief   This function will unlock the spinlock, will unlock the thread scheduler.
 *
 * @param   lock is a pointer to the spinlock.
 */
void rt_spin_unlock(struct rt_spinlock *lock)
{
    rt_base_t critical_level;
    RT_SPIN_UNLOCK_DEBUG(lock, critical_level);
    rt_exit_critical_safe(critical_level);
}

/**
 * @brief   This function will disable the local interrupt and then lock the spinlock, will lock the thread scheduler.
 *
 * @note    If the spinlock is locked, the current CPU will keep polling the spinlock state
 *          until the spinlock is unlocked.
 *
 * @param   lock is a pointer to the spinlock.
 *
 * @return  Return current cpu interrupt status.
 */
rt_base_t rt_spin_lock_irqsave(struct rt_spinlock *lock)
{
    rt_base_t level;
    RT_UNUSED(lock);
    level = rt_hw_interrupt_disable();
    rt_enter_critical();
    RT_SPIN_LOCK_DEBUG(lock);
    return level;
}

/**
 * @brief   This function will unlock the spinlock and then restore current cpu interrupt status, will unlock the thread scheduler.
 *
 * @param   lock is a pointer to the spinlock.
 *
 * @param   level is interrupt status returned by rt_spin_lock_irqsave().
 */
void rt_spin_unlock_irqrestore(struct rt_spinlock *lock, rt_base_t level)
{
    rt_base_t critical_level;
    RT_SPIN_UNLOCK_DEBUG(lock, critical_level);
    rt_exit_critical_safe(critical_level);
    rt_hw_interrupt_enable(level);
}
