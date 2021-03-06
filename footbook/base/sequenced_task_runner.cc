﻿/**
* @Author: YangGuang
* @Date:   2018-10-23
* @Email:  guang334419520@126.com
* @Filename: sequenced_task_runner.h
* @Last modified by:  YangGuang
*/
#include "base/sequenced_task_runner.h"

#include <utility>
#include <functional>

#include "bind_util.h"

namespace base {

bool SequencedTaskRunner::PostNonNestableTask(const Location & from_here,
											  OnceClosure task) {
	return PostNonNestableDelayedTask(from_here, std::move(task),
									  std::chrono::milliseconds(0));
}

SequencedTaskRunner::~SequencedTaskRunner() = default;

bool 
SequencedTaskRunner::DeleteOrReleaseSoonInternal(const Location & from_here,
												 void(*deleter)(const void *), 
												 const void * object)  {
	return PostNonNestableTask(from_here, base::BindOnceClosure(deleter, object));
}

OnTaskRunnerDeleter::OnTaskRunnerDeleter(
	std::shared_ptr<SequencedTaskRunner> task_ruuner)
	: task_runner_(std::move(task_ruuner)) {
}

OnTaskRunnerDeleter::~OnTaskRunnerDeleter() = default;

OnTaskRunnerDeleter::OnTaskRunnerDeleter(OnTaskRunnerDeleter &&) = default;

OnTaskRunnerDeleter & OnTaskRunnerDeleter::operator=(
	OnTaskRunnerDeleter &&) = default;

}	// namespace base.

