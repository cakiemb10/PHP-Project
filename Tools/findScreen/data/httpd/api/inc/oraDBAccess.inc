<?php
/*========================================================*/
// ��������
//   ��2007/08/03 Y.Matsukawa   LOG�������ޤؤ���³���ɲ�
//   ��2016/06/27 H.Osamoto		Ź�޾����ǧ�ڥǡ����λ�����DB��ʬΥ
/*========================================================*/
/**
 * oraDBAccess class
 * oracle DB Server�ؤΥǡ��������������饹
 * ��³�ѥ�᡼����[ default.inc ]�򻲾�
 ***/
class oraDBAccess {

	var $conn;		# DB connection
	var $tns;		# ��³�����ӥ�̾
	var $user;		# ��³�桼��
	var $password;		# ��³�ѥ����

	/**
	 * function	��	oraDBAccess
	 *
	 * ��ǽ		��	oraDBAccess ���󥹥ȥ饯��
	 * �����	��	�ʤ�
	 ***/
	function oraDBAccess($scm="emap"){
		$this->init($scm);
	}

	/**
	 * function	��	init
	 *
	 * ��ǽ		��	DB�꥽�����ν��������
	 * �����	��	�ʤ�
	 ***/
	function init($scm){
		$this->conn = null;
		switch ($scm) {
			case "log":
				$this->tns      = ORA_TNS_LOG;
				$this->user     = ORA_USER_LOG;
				$this->password = ORA_PASS_LOG;
				break;
			// add 2016/06/27 H.Osamoto [
			case "auth":
				$this->tns      = ORA_TNS_AUTH;
				$this->user     = ORA_USER;
				$this->password = ORA_PASS;
				break;
			// add 2016/06/27 H.Osamoto ]
			default: // emap
				$this->tns      = ORA_TNS;
				$this->user     = ORA_USER;
				$this->password = ORA_PASS;
		}
	}

	/**
	 * function	��	open
	 *
	 * ��ǽ		��	DB��³����
	 * �����	��	������	true
	 *		  		���Ի�	false
	 ***/
	function open(){
		$this->conn = OCILogon(
			"$this->user",
			"$this->password",
			"$this->tns"
		);
		if(!$this->conn){
			return false;
		}
		return true;
	}

	/**
	 *
	 * function	��	free
	 * ��ǽ		��	�꥽�����γ���
	 * �����	��	�ʤ�
	 ***/
	function free($stmt){
		if($stmt){
			OCIFreeStatement($stmt);
		}
	}

	/**
	 *
	 * function	��	close
	 * ��ǽ		��	DB���ǽ���
	 * �����	��	�ʤ�
	 ***/
	function close(){
		if($this->conn){
			OCILogOff($this->conn);
			$this->conn = false;
		}
		$this->destroy();
	}

	/**
	 * function	��	destroy
	 *
	 * ��ǽ		��	���곫������
	 * �����	��	�ʤ�
	 ***/
	function destroy(){
		$this->tns		= "";
		$this->user		= "";
		$this->password	= "";
		$this->conn		= "";
	}

	/**
	 * function	��	getRecord
	 *
	 * ��ǽ		��	�쥳���ɥǡ�����������
	 * ����		��	��������ID
	 * �����	��	������	�쥳���ɥǡ�����Ǽ����
	 *	  		���Ի�	false
	 ***/
	function getRecord($stmt){
		if( ! $stmt ) return false;
		return OCIFetch($stmt);
	}

	/**
	 * function	��	getRecInto
	 *
	 * ��ǽ		��	�쥳���ɥǡ�����������
	 * ����		��	��������ID
	 *		��	�ǡ�����Ǽ����
	 *		��	���ϥ⡼��
	 * �����	��	������	�쥳���ɥǡ�����Ǽ����
	 *	  		���Ի�	false
	 ***/
	function getRecInto($stmt, &$result, $mode){
		if( ! $stmt ) return false;
		return OCIFetchInto($stmt,&$result,$mode);
	}

	/**
	 * function	��	getResult
	 *
	 * ��ǽ		��	�쥳���ɥǡ�����������
	 * ����		��	��������ID
	 *		��	�����ID
	 * �����	��	������	�쥳���ɥǡ�����Ǽ����
	 *		  	���Ի�	false
	 ***/
	function getResult($stmt,$col){
		if( (! $stmt)||($col=="") ) return false;
		return OCIResult($stmt,$col);
	}

	/**
	 * function	��	getRowCount
	 *
	 * ��ǽ		��	SQL�¹Է�̷����������
	 * ����		��	��������ID
	 * �����	��	������	�쥳���ɷ��
	 *		  		���Ի�	false
	 ***/
	function getRowCount($stmt){
		if( ! $stmt ) return false;
		return OCIRowCount($stmt);
	}

	/**
	 * function	��	getColCount
	 *
	 * ��ǽ		��	��������������
	 * ����		��	��������ID
	 * �����	��	������	�������
	 *		  		���Ի�	false
	 ***/
	function getColCount($stmt){
		if( ! $stmt ) return false;
		return OCINumCols($stmt);
	}

	/**
	 * function	��	discripter
	 *
	 * ��ǽ		��	�����ΰ�����
	 * ����		��	�ʤ�
	 * �����	��	������	true
	 *		  		���Ի�	false
	 ***/
	function discripter(){
		if( ! $this->conn ) return false;
		return OCINewDescriptor($this->conn,OCI_D_ROWID);
	}

	/**
	 * function	��	defineByName
	 *
	 * ��ǽ		��	����Ѥ� PHP �ѿ������
	 * ����		��	@$cur	--��������ID
	 * 			��	@$vname	--�ѿ�̾
	 * 			��	@$pname	--SQL�����̾ "xxx"
	 * 			��	@$type	--������
	 * �����	��	������	true
	 *		  		���Ի�	false
	 ***/
	function defineByName($stmt,$vname,$pname,$type=0){
		if( (! $stmt)||($vname=="")||($pname=="") ){
			return false;
		} else if(! OCIDefineByName($stmt,$vname,$pname,$type) ) {
			return false;
		}
		return true;
	}

	/**
	 * function	��	bindByName
	 *
	 * ��ǽ		��	�ѥ�᡼��Bind����
	 * ����		��	@$cur	--��������ID
	 * 			��	@$vname	--�ѿ�̾
	 * 			��	@$pname	--SQL�ѥ�᡼�� "xxx:"
	 * 			��	@$len	--Ĺ��
	 * 			��	@$type	--������
	 * �����	��	������	true
	 *		  		���Ի�	false
	 ***/
	function bindByName($stmt,$vname,$pname,$len,$type=0){
		//if( ($stmt=="")||($vname=="")||($pname=="")||($len=="") ){
		if( ($stmt=="")||($vname=="")||($len=="") ){
			return false;
		} else if(! OCIBindByName($stmt,$vname,$pname,$len,$type) ) {
			return false;
		}
		return true;
	}

	/**
	 * function	��	getColumnType
	 *
	 * ��ǽ		��	����෿��������
	 * ����		��	��������ID
	 *			��	�����
	 * �����	��	������	����෿��ʸ����
	 *		  		���Ի�	false
	 ***/
	function getColumnType($stmt,$column){
		if( (! $stmt)||($column=="") ) return false;
		return OCIColumnType($stmt,$column);
	}

	/**
	 * function	��	getColumnSize
	 *
	 * ��ǽ		��	����ॵ������������
	 * ����		��	��������ID
	 *			��	�����
	 * �����	��	������	����ॵ������ʸ����
	 *		  		���Ի�	false
	 ***/
	function getColumnSize($stmt,$column){
		if( (! $stmt)||($column=="") ) return false;
		return OCIColumnSize($stmt,$column);
	}

	/**
	 * function	��	getColumnName
	 *
	 * ��ǽ		��	�����̾��������
	 * ����		��	��������ID
	 *			��	�����
	 * �����	��	������	�����̾��ʸ����
	 *		  		���Ի�	false
	 ***/
	function getColumnName($stmt,$column){
		if( (! $stmt)||($column=="") ) return false;
		return OCIColumnName($stmt,$column);
	}

	/**
	 * function	��	getError
	 *
	 * ��ǽ		��	���顼��å�������������
	 * ����		��	���ơ��ȥ���
	 * �����	��	������	���顼��å�����
	 *		  		���Ի�	false
	 ***/
	function getError($stmt){
		if(! $stmt) return false;
		return OCIError($stmt);
	}

	/**
	 * function	��	sqlExecute
	 *
	 * ��ǽ		��	SQL�䤤��碌�¹Խ���
	 * ����		��	SQLʸ
	 * 			��	��������ID
	 * �����	��	������	true
	 *		  		���Ի�	false
	 ***/
	function sqlExecute($sql,&$stmt){

//***********	FOR DEBUG
//print("$sql<br>\n");
//***********	FOR END
		if( $sql=="" ) return false;

		$stmt = OCIParse($this->conn, $sql);
		if( ! $stmt ){
			return false;
		} else if( ! OCIExecute($stmt, OCI_DEFAULT) ){
			return false;
		}
		return true;
	}

	/**
	 * function	��	rollbackTransaction
	 *
	 * ��ǽ		��	�ȥ�󥶥�����������Хå�
	 * ����		��	�ʤ�
	 * �����	��	�ʤ�
	 ***/
	function rollbackTransaction(){
		if( ! OCIRollback($this->conn) ) return false;
		return true;
	}

	/**
	 * function	��	commitTransaction
	 *
	 * ��ǽ		��	�ȥ�󥶥�����󥳥ߥå�
	 * ����		��	�ʤ�
	 * �����	��	�ʤ�
	 ***/
	function commitTransaction(){
		if( ! OCICommit($this->conn) ) return false;
		return true;
	}
	
	function parse($sql) {
		return OCIPARSE($this->conn, $sql);
	}
	
	function execute($stmt) {
		return OCIExecute($stmt, OCI_DEFAULT);
	}
}
?>