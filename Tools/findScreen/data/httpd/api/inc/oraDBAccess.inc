<?php
/*========================================================*/
// 更新履歴
//   ・2007/08/03 Y.Matsukawa   LOGスキーマへの接続を追加
//   ・2016/06/27 H.Osamoto		店舗情報と認証データの参照先DBを分離
/*========================================================*/
/**
 * oraDBAccess class
 * oracle DB Serverへのデータアクセスクラス
 * 接続パラメータは[ default.inc ]を参照
 ***/
class oraDBAccess {

	var $conn;		# DB connection
	var $tns;		# 接続サービス名
	var $user;		# 接続ユーザ
	var $password;		# 接続パスワード

	/**
	 * function	：	oraDBAccess
	 *
	 * 機能		：	oraDBAccess コンストラクタ
	 * 戻り値	：	なし
	 ***/
	function oraDBAccess($scm="emap"){
		$this->init($scm);
	}

	/**
	 * function	：	init
	 *
	 * 機能		：	DBリソースの初期化処理
	 * 戻り値	：	なし
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
	 * function	：	open
	 *
	 * 機能		：	DB接続処理
	 * 戻り値	：	成功時	true
	 *		  		失敗時	false
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
	 * function	：	free
	 * 機能		　	リソースの開放
	 * 戻り値	：	なし
	 ***/
	function free($stmt){
		if($stmt){
			OCIFreeStatement($stmt);
		}
	}

	/**
	 *
	 * function	：	close
	 * 機能		　	DB切断処理
	 * 戻り値	：	なし
	 ***/
	function close(){
		if($this->conn){
			OCILogOff($this->conn);
			$this->conn = false;
		}
		$this->destroy();
	}

	/**
	 * function	：	destroy
	 *
	 * 機能		：	メモリ開放処理
	 * 戻り値	：	なし
	 ***/
	function destroy(){
		$this->tns		= "";
		$this->user		= "";
		$this->password	= "";
		$this->conn		= "";
	}

	/**
	 * function	：	getRecord
	 *
	 * 機能		　	レコードデータ取得処理
	 * 引数		：	カーソルID
	 * 戻り値	：	成功時	レコードデータ格納配列
	 *	  		失敗時	false
	 ***/
	function getRecord($stmt){
		if( ! $stmt ) return false;
		return OCIFetch($stmt);
	}

	/**
	 * function	：	getRecInto
	 *
	 * 機能		　	レコードデータ取得処理
	 * 引数		：	カーソルID
	 *		：	データ格納配列
	 *		：	出力モード
	 * 戻り値	：	成功時	レコードデータ格納配列
	 *	  		失敗時	false
	 ***/
	function getRecInto($stmt, &$result, $mode){
		if( ! $stmt ) return false;
		return OCIFetchInto($stmt,&$result,$mode);
	}

	/**
	 * function	：	getResult
	 *
	 * 機能		　	レコードデータ取得処理
	 * 引数		：	カーソルID
	 *		：	カラムID
	 * 戻り値	：	成功時	レコードデータ格納配列
	 *		  	失敗時	false
	 ***/
	function getResult($stmt,$col){
		if( (! $stmt)||($col=="") ) return false;
		return OCIResult($stmt,$col);
	}

	/**
	 * function	：	getRowCount
	 *
	 * 機能		　	SQL実行結果件数取得処理
	 * 引数		：	カーソルID
	 * 戻り値	：	成功時	レコード件数
	 *		  		失敗時	false
	 ***/
	function getRowCount($stmt){
		if( ! $stmt ) return false;
		return OCIRowCount($stmt);
	}

	/**
	 * function	：	getColCount
	 *
	 * 機能		　	カラム数取得処理
	 * 引数		：	カーソルID
	 * 戻り値	：	成功時	カラム件数
	 *		  		失敗時	false
	 ***/
	function getColCount($stmt){
		if( ! $stmt ) return false;
		return OCINumCols($stmt);
	}

	/**
	 * function	：	discripter
	 *
	 * 機能		　	記憶領域を確保
	 * 引数		：	なし
	 * 戻り値	：	成功時	true
	 *		  		失敗時	false
	 ***/
	function discripter(){
		if( ! $this->conn ) return false;
		return OCINewDescriptor($this->conn,OCI_D_ROWID);
	}

	/**
	 * function	：	defineByName
	 *
	 * 機能		　	定義用の PHP 変数を使用
	 * 引数		：	@$cur	--カーソルID
	 * 			：	@$vname	--変数名
	 * 			：	@$pname	--SQLカラム名 "xxx"
	 * 			：	@$type	--タイプ
	 * 戻り値	：	成功時	true
	 *		  		失敗時	false
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
	 * function	：	bindByName
	 *
	 * 機能		　	パラメータBind処理
	 * 引数		：	@$cur	--カーソルID
	 * 			：	@$vname	--変数名
	 * 			：	@$pname	--SQLパラメータ "xxx:"
	 * 			：	@$len	--長さ
	 * 			：	@$type	--タイプ
	 * 戻り値	：	成功時	true
	 *		  		失敗時	false
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
	 * function	：	getColumnType
	 *
	 * 機能		　	カラム型取得処理
	 * 引数		：	カーソルID
	 *			：	カラム
	 * 戻り値	：	成功時	カラム型の文字列
	 *		  		失敗時	false
	 ***/
	function getColumnType($stmt,$column){
		if( (! $stmt)||($column=="") ) return false;
		return OCIColumnType($stmt,$column);
	}

	/**
	 * function	：	getColumnSize
	 *
	 * 機能		　	カラムサイズ取得処理
	 * 引数		：	カーソルID
	 *			：	カラム
	 * 戻り値	：	成功時	カラムサイズの文字列
	 *		  		失敗時	false
	 ***/
	function getColumnSize($stmt,$column){
		if( (! $stmt)||($column=="") ) return false;
		return OCIColumnSize($stmt,$column);
	}

	/**
	 * function	：	getColumnName
	 *
	 * 機能		　	カラム名取得処理
	 * 引数		：	カーソルID
	 *			：	カラム
	 * 戻り値	：	成功時	カラム名の文字列
	 *		  		失敗時	false
	 ***/
	function getColumnName($stmt,$column){
		if( (! $stmt)||($column=="") ) return false;
		return OCIColumnName($stmt,$column);
	}

	/**
	 * function	：	getError
	 *
	 * 機能		　	エラーメッセージ取得処理
	 * 引数		：	ステートメント
	 * 戻り値	：	成功時	エラーメッセージ
	 *		  		失敗時	false
	 ***/
	function getError($stmt){
		if(! $stmt) return false;
		return OCIError($stmt);
	}

	/**
	 * function	：	sqlExecute
	 *
	 * 機能		　	SQL問い合わせ実行処理
	 * 引数		：	SQL文
	 * 			：	カーソルID
	 * 戻り値	：	成功時	true
	 *		  		失敗時	false
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
	 * function	：	rollbackTransaction
	 *
	 * 機能		　	トランザクションロールバック
	 * 引数		：	なし
	 * 戻り値	：	なし
	 ***/
	function rollbackTransaction(){
		if( ! OCIRollback($this->conn) ) return false;
		return true;
	}

	/**
	 * function	：	commitTransaction
	 *
	 * 機能		　	トランザクションコミット
	 * 引数		：	なし
	 * 戻り値	：	なし
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
